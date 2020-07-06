#ifndef RTU_H_
#define RTU_H_

#include <stdint.h>

int rtuParse(uint8_t *buf, uint8_t len);
uint16_t crcCheck(uint8_t *data, uint8_t size);
int dataBack();
#endif
