#ifndef __RTU_H_
#define __RTU_H_

#include "rtu.h"
#include "main.h"
#include "radar.h"
#include "global.h"
#include "usart.h"

uint16_t crcCheck(uint8_t *data, uint8_t size)
{
	uint8_t i0,i1;
	uint8_t CRClo,CRChi;
	uint8_t savehi,savelo;
	CRClo = CRChi = 0xff;
	for(i0=0; i0<size; i0++)	{
		CRClo = CRClo^*(data+i0);
		for(i1=0; i1<8; i1++) {
			savehi = CRChi;
			savelo = CRClo;
			CRChi>>=1;
			CRClo>>=1;
			if((savehi&1) == 1) {
				CRClo |= 0x80;
			}
			if((savelo&1) == 1) {
				CRChi ^= 0xA0;
				CRClo ^= 1;
			}
		}
	}
	return (CRChi<<8) | CRClo;
}

#define RTU_EXCEPT1 1
#define RTU_EXCEPT2 2
#define RTU_EXCEPT3 3
#define RTU_EXCEPT4 4


int rtuExpRsp(uint8_t rtuExp, uint8_t *data)
{
	int ret = -1;
	data[1] |= 0x80;
	switch(rtuExp) {
		case RTU_EXCEPT1:
			data[2] = 1;
			break;
		case RTU_EXCEPT2:
			data[2] = 2;
			break;
		case RTU_EXCEPT3:
			data[2] = 3;
			break;
		case RTU_EXCEPT4:
			data[2] = 4;
		default: ;
	}
	data[3] = crcCheck(data, 3) & 0xff;
	data[4] = crcCheck(data, 3) >> 8;
	HAL_UART_Transmit_IT(&huart1, data, 5);
	return ret;
}

extern const uint16_t  reflection_count_max;
extern acc_detector_distance_peak_reflection_t reflections[5];
extern acc_detector_distance_peak_result_info_t result_info;
extern acc_detector_distance_peak_handle_t handle;
extern uint8_t configUart;

const uint8_t zero = 0;
uint8_t *configuration[52] = {(uint8_t *)&config.pid + 1, (uint8_t *)&config.pid, (uint8_t *)&config.vid + 1,
		(uint8_t *)&config.vid, &zero, &config.addr, &zero, &config.baudrate, &config.parity, &config.stopBit,
		&zero, &config.number, (uint8_t *)&config.distance1 + 1, (uint8_t *)&config.distance1, (uint8_t *)&config.amplitude1 + 1,
		(uint8_t *)&config.amplitude1, (uint8_t *)&config.distance2 + 1, (uint8_t *)&config.distance2, (uint8_t *)&config.amplitude2 + 1,
		(uint8_t *)&config.amplitude2, (uint8_t *)&config.distance3 + 1, (uint8_t *)&config.distance3, (uint8_t *)&config.amplitude3 + 1,
		(uint8_t *)&config.amplitude3, (uint8_t *)&config.distance4 + 1, (uint8_t *)&config.distance4, (uint8_t *)&config.amplitude4 + 1,
		(uint8_t *)&config.amplitude4, (uint8_t *)&config.distance5 + 1, (uint8_t *)&config.distance5, (uint8_t *)&config.amplitude5 + 1,
		(uint8_t *)&config.amplitude5, &zero, &config.sort, (uint8_t *)&config.start + 1, (uint8_t *)&config.start, (uint8_t *)&config.stop + 1,
		(uint8_t *)&config.stop, (uint8_t *)&config.threshold + 1, (uint8_t *)&config.threshold, &zero,
		&config.average, &zero, &config.relate, &zero, &config.profile, &zero, &config.measureMode,
		(uint8_t *)&config.compareLength + 1, (uint8_t *)&config.compareLength, &zero, &config.powerSaveMode};
int rtuParse (uint8_t *data,uint8_t len)
{

    int ret = -1;
    uint8_t pdata[256];
	for(uint8_t i=0; i<len; i++) {
		pdata[i] = ((uint8_t *)data)[i];
	}
    switch (pdata[1]) {
		case 0x03:
			if(pdata[0]) {
				if (pdata[4] || !pdata[5] || (pdata[5] > 0x1A)) {
					rtuExpRsp(RTU_EXCEPT3, pdata);
				} else if ( !pdata[2] && (pdata[3] + pdata[5] < 0x1B)) {
					uint8_t addr = pdata[3];
					uint8_t num = pdata[5] * 2;
					pdata[2] = num;
					if (config.measureMode == 0 && !(addr > 0x0F || ((addr + num/2) < 0x05))) {
						/*
						CLEAR_BIT(huart1.Instance->CR1, USART_CR1_TE);
						(&huart1)->gState = HAL_UART_STATE_BUSY;
						acc_detector_distance_peak_activate(handle);
						SET_BIT(huart1.Instance->CR1, USART_CR1_TE);
						huart1.gState = HAL_UART_STATE_READY;
						*/
						execDetOnce(handle, reflections, reflection_count_max, &result_info);
						/*
						CLEAR_BIT(huart1.Instance->CR1, USART_CR1_TE);
						(&huart1)->gState = HAL_UART_STATE_BUSY;
						acc_detector_distance_peak_deactivate(handle);
						SET_BIT(huart1.Instance->CR1, USART_CR1_TE);
						huart1.gState = HAL_UART_STATE_READY;
						*/
					}
					for (uint8_t temp = 0; temp < num; temp++) {
						pdata[3 + temp] = *configuration[addr * 2 + temp];
					}
					pdata[3 + num] = crcCheck(pdata, 3 + num) & 0xff;
					pdata[4 + num] = crcCheck(pdata, 3 + num) >> 8;
					HAL_UART_Transmit_IT(&huart1, pdata, 5 + num);
					ret = 0;
				} else {
					rtuExpRsp(RTU_EXCEPT2, pdata);
				}
			}
			break;
		case 0x06:
			if(pdata[2] || (pdata[3] > 0x19) || (pdata[3] < 2) || (pdata[3] > 4 && pdata[3] < 0X10)) {
				rtuExpRsp(RTU_EXCEPT2, pdata);
			}else {
				uint8_t addr = pdata[3], dataHi = pdata[4], dataLo = pdata[5];
				if (((addr == 0x02) && (dataHi || dataLo > 0xF7 || !dataLo)) || ((addr == 0x03) && (dataHi))||(addr == 0x10 && (dataHi || dataLo > 1)) || (((addr == 0x11) ||
						(addr == 0x12)) && (((dataHi<<8)+dataLo) < 0x46 || ((dataHi<<8)+dataLo) > 0x19C0))|| ((addr == 0x12 && (((dataHi<<8)+dataLo) <= config.start))) ||
						((addr == 0x11) && ((dataHi<<8)+dataLo)>=config.stop) ||((addr == 0x13) && (((dataHi<<8)+dataLo) < 0x64 || ((dataHi<<8)+dataLo) > 0x2701)) || ((addr == 0x14) && (dataHi || !dataLo ||
						dataLo>0x3F)) || ((addr == 0X15) && (dataHi || dataLo > 0x64)) || ((addr == 0x16) && (dataHi || (dataLo>4))) ||((addr == 0x17) && (dataHi || dataLo > 1))
						|| ((addr == 0x18) && (((dataHi<<8)+dataLo) < 0x46 || ((dataHi<<8)+dataLo) > 0x19C0)) || ((addr == 0x19) && (dataHi || dataLo>3))) {
					rtuExpRsp(RTU_EXCEPT3, pdata);
				} else {
					if((addr == 0x03 && (dataLo != config.baudrate)) || (addr == 0x04 && (((dataHi<<8)+dataLo) != ((config.parity<<8)+config.stopBit)))) {
						configUart = 1;
					}
					*(configuration[addr * 2]) = dataHi;
					*(configuration[addr * 2 + 1]) = dataLo;
					storeConfig();
					if(pdata[0]) {
						HAL_UART_Transmit_IT(&huart1, pdata, 8);
					}
					ret = 1;
				}
			}
			break;
		case 0x10:
			if (pdata[4] || !pdata[5] || (pdata[6] != pdata[5] * 2) || (pdata[5] > 0x0B)) {
				rtuExpRsp(RTU_EXCEPT3, pdata);
			} else if ( !pdata[2] && ((pdata[3]>1 && pdata[3]<5 && pdata[3]+pdata[5]<6) || (pdata[3]>0x0F && pdata[3]+pdata[5]<0x1B))) {
				uint8_t addr;
				uint8_t dataHi, dataLo;
				uint16_t temp = 0, temp1 = 0;
				for (uint8_t i=0; i < pdata[5]; i++) {
					dataHi = pdata[7 + 2 * i];
					dataLo = pdata[8 + 2 * i];
					addr = pdata[3] + i;
					if(!configUart &&((addr == 0x03 && (dataLo != config.baudrate)) || (addr == 0x04 && ((dataHi<<8)+dataLo != (config.parity<<8)+config.stopBit)))) {
						configUart = 1;
					}
					if (((addr == 0x02) && (dataHi || dataLo > 0xF7 || !dataLo)) || ((addr == 0x03) && (dataHi))||(addr == 0x10 && (dataHi || dataLo > 1)) || (((addr == 0x11) ||
							(addr == 0x12)) && (((dataHi<<8)+dataLo) < 0x46 || ((dataHi<<8)+dataLo) > 0x19C0)) || ((addr == 0x13) && (((dataHi<<8)+dataLo) < 0x64 || ((dataHi<<8)+dataLo) > 0x2701)) || ((addr == 0x14) && (dataHi || !dataLo ||
							dataLo>0x3F)) || ((addr == 0X15) && (dataHi || dataLo > 0x64)) || ((addr == 0x16) && (dataHi || (dataLo>4))) ||((addr == 0x17) && (dataHi || dataLo > 1))
							|| ((addr == 0x18) && (((dataHi<<8)+dataLo) < 0x46 || ((dataHi<<8)+dataLo) > 0x19C0)) || ((addr == 0x19) && (dataHi || dataLo>3))) {
						rtuExpRsp(RTU_EXCEPT3, pdata);
						goto out;
					}
					if (addr == 0x11) {
						temp = (dataHi << 8) + dataLo;
					}
					if (addr == 0x12) {
						temp1 = (dataHi << 8) + dataLo;
					}
				}

				if ((temp && temp1 &&(temp >= temp1)) ||(temp && !temp1 && (temp>= config.stop)) || (!temp && temp1 && (temp1 <= config.start))) {
					rtuExpRsp(RTU_EXCEPT3, pdata);
					goto out;
				}
				for (uint8_t i=0; i<pdata[6]; i++) {
					*(configuration[pdata[3] * 2 + i]) = pdata[7+i];
				}
				storeConfig();
				ret = 1;
				if(pdata[0]) {
					pdata[6] = crcCheck(pdata, 6) & 0xff;
					pdata[7] = crcCheck(pdata, 6) >> 8;
					HAL_UART_Transmit_IT(&huart1, pdata, 8);
				}

			} else {
				rtuExpRsp(RTU_EXCEPT2,pdata);
			}
			break;
    	default:
    	    if(pdata[0])
				rtuExpRsp(RTU_EXCEPT1,pdata);
    }
out:
	return ret;

}


#endif
