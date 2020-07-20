#ifndef __GLOBAL_H_
#define __GLOBAL_H_

#include <stdint.h>
#include <stm32l4xx.h>

typedef enum {
	MODE_ON_DEMAND,
	MODE_AT_FREQUENCY,
} eMode_t;
extern  eMode_t MODE;

typedef struct {
	uint8_t destAddr;
	uint8_t cmd;
	uint8_t addr[2];
	uint8_t num[2];
	//uint8_t len;
	//uint8_t data[len];
	//uint8_t crc[2];
} sRtuHead_t;

#pragma pack(push)
#pragma pack(1)
typedef struct {
	uint16_t pid;
	uint16_t vid;
	uint8_t addr;
	uint8_t baudrate;
	uint8_t parity;
	uint8_t stopBit;
	uint8_t number;
	uint16_t distance1;
	uint16_t amplitude1;
	uint16_t distance2;
	uint16_t amplitude2;
	uint16_t distance3;
	uint16_t amplitude3;
	uint16_t distance4;
	uint16_t amplitude4;
	uint16_t distance5;
	uint16_t amplitude5;
	uint8_t sort;
	uint16_t start;
	uint16_t stop;
	//uint8_t thresholdMode;
	uint16_t threshold;
	uint8_t average;
	uint8_t relate;
	//uint8_t resolution;
	uint8_t profile;
	uint8_t measureMode;
	uint16_t compareLength;
	//uint8_t compareSwitch;
	uint8_t powerSaveMode;
	//uint8_t calibration;
	uint8_t no[5];
} sConfig_t;

#pragma pack(pop)

extern sConfig_t config;

void storeConfig();
void restoreConfig(void);
void getConfig(sConfig_t *p);
void writeCali(uint64_t data);


#endif
