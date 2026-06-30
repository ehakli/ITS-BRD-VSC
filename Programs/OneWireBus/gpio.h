#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
#include <limits.h>

#define PIN_PD01             0x1
#define PIN_PD00             0x0
#define READ_ROM_COMMAND     0x33
#define SKIP_ROM_COMMAND     0xCC
#define MATCH_ROM_COMMAND    0x55
#define CONVERT_T_COMMAND    0x44
#define READ_SCRATCHPAD      0xBE
#define CRC_LENGTH           7
#define CRC_POS              7
#define FAMILY_DS18B20       0x28
#define FAMILY_DS18S20       0x10
#define MAX_SENSORS 5


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
uint8_t check_crc(uint8_t *data, uint8_t len);

void startConversion(void);
int16_t rawToTemp_x16(uint8_t *scratchpad, uint8_t family_code);
int16_t readTemperature(uint8_t *rom_id);
void displayTemperatures(void);

#endif // GPIO_H