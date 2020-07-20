#include "global.h"
#include "string.h"
#include "stm32l4xx_hal_flash.h"
#include "stdint.h"

sConfig_t config = {.pid=0x0002, .vid=0x0010, .addr=0x0C, .baudrate=0x03, .parity=0, .stopBit=0x01, .number=0,
		0xffff, 0, 0xffff, 0, 0xffff, 0, 0xffff, 0, 0xffff, 0,
		.sort = 0, .start=0x00C8, .stop = 0x19C0, 0x0190, 0x0A, 0x46, 0x02, 0x01, 0x012C, 0x03};

static void readFlash(uint32_t addr, void *buf, uint16_t count)
{
	int i;
	uint8_t *p = (uint8_t *)buf;
	for (i = 0; i < count; i++) {
		p[i] = *(uint8_t *)addr;
		addr += 1;
	}

}

#define RADAR_CONFIG_ADDRESS 0x8032000
#define RADAR_CALI_ADDRESS   0x8032800
static FLASH_EraseInitTypeDef eraseInit = {FLASH_TYPEERASE_PAGES, FLASH_BANK_1, 100, 1};
static FLASH_EraseInitTypeDef eraseCaInit = {FLASH_TYPEERASE_PAGES, FLASH_BANK_1, 101, 1};

static void writeFlash(void *data, uint8_t len)
{
	uint32_t addr = RADAR_CONFIG_ADDRESS;
	uint32_t pageError = 0;

	__disable_irq();
	HAL_FLASH_Unlock();
	HAL_FLASHEx_Erase(&eraseInit, &pageError);
	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGAERR | FLASH_FLAG_WRPERR);
	for(uint8_t i=0; i < len; ) {
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, addr, *((uint64_t *)data + i/8));
		addr += 8;
		i += 8;
	}

	HAL_FLASH_Lock();
	__enable_irq();

}

void storeConfig(){
	writeCali(0);
	writeFlash(&config, 48);
	writeCali(0x0102030401020304);
}

void restoreConfig(void){
	readFlash(RADAR_CONFIG_ADDRESS, &config, 48);
}

void getConfig(sConfig_t *p){
	readFlash(RADAR_CONFIG_ADDRESS, p, 48);
}

void writeCali(uint64_t data)
{
	uint32_t addr = RADAR_CALI_ADDRESS;
	uint32_t pageError = 0;
	__disable_irq();
	HAL_FLASH_Unlock();
	HAL_FLASHEx_Erase(&eraseCaInit, &pageError);
	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGAERR | FLASH_FLAG_WRPERR);
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, addr, data);
	HAL_FLASH_Lock();
	__enable_irq();
}
