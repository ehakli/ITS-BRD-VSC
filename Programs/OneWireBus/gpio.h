#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

void initPD1(void);
void initPD0(void);

void setIOHigh(void);
void setIOLow(void);

uint8_t reset(void);
void writeZero(void);
void writeOne(void);
uint8_t readBit(void);

void writeByte(uint8_t byte);
uint8_t readByte(void);

void readRom(void);

#endif // GPIO_H