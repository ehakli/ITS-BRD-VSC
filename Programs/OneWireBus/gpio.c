#include <stdint.h>
#include <limits.h>
#include "lcd.h"
#include <stdio.h>
#include "LCD_GUI.h"
#include "stm32f429xx.h"
#include "mysleep.h"
#include "gpio.h"

uint8_t romdata[8];

void readRom(void)
{
   
    lcdGotoXY(0, 0);
    if (reset() == 1)
    {
        writeByte(READ_ROM_COMMAND);

        for (int i = 0; i < 8; i++)
        {
            romdata[i] = readByte();
        }

        uint8_t calculated_crc = check_crc(romdata, CRC_LENGTH);

        if (calculated_crc == romdata[CRC_POS])
        {
            lcdPrintlnS("ROM: ");
            for (int b = 0; b < 8; b++)
            {
                char buf[32];
                snprintf(buf, sizeof(buf), "%02X ", romdata[b]);
                lcdPrintlnS(buf);
            }
            char buf[32];
            snprintf(buf, sizeof(buf), "\nFamily Code: %02X\n", romdata[0]);
            lcdPrintlnS(buf);
            lcdPrintlnS("CRC OK\n");
        }
        else
        {
            char buf[64];
            snprintf(buf, sizeof(buf), "CRC FEHLER! BERECHNET: %02X, EMPFANGEN: %02X\n", calculated_crc, romdata[CRC_POS]);
            lcdPrintlnS(buf);
        }
    }
    else
    {
        lcdPrintS("Kein Sensor gefunden!\n");
    }
}

uint8_t check_crc(uint8_t *data, uint8_t len)
{
    uint8_t crc = 0;

    for (int i = 0; i < len; i++)
    {
        uint8_t byte = data[i];
        for (int j = 0; j < 8; j++)
        {
            uint8_t calculated = (crc ^ byte) & 0x01;
            crc = crc >> 1;
            if (calculated)
            {
                crc ^= 0x8C;
            }
            byte = byte >> 1;
        }
    }

    return crc;
}

uint8_t readByte(void)
{
    uint8_t value = 0;

    for (int i = 0; i < 8; i++)
    {
        uint8_t bit = readBit();
        value |= (bit << i);
    }

    return value;
}

void writeByte(uint8_t byte)
{
    for (int i = 0; i < 8; i++)
    {
        uint8_t bit = (byte >> i) & 1;
        if (bit == 1)
        {
            writeOne();
        }
        else
        {
            writeZero();
        }
    }
}

uint8_t reset(void)
{
    setIOLow();
    sleep(480);
    setIOHigh();
    sleep(70);

    uint8_t pulse = 0;

    if ((GPIOD->IDR & (1 << PIN_PD00)) == 0)
    {
        pulse = 1;
    }

    sleep(410);
    return pulse;
}

uint8_t readBit(void)
{
    uint8_t bit = 0;

    setIOLow();
    sleep(6);
    setIOHigh();
    sleep(9);

    if (GPIOD->IDR & (1 << PIN_PD00))
    {
        bit = 1;
    }

    sleep(55);

    return bit;
}

void writeZero(void)
{
    setIOLow();
    sleep(60);
    setIOHigh();
    sleep(10);
}

void writeOne(void)
{
    setIOLow();
    sleep(6);
    setIOHigh();
    sleep(64);
}

void setIOHigh(void)
{
    GPIOD->BSRR = (1 << PIN_PD00);
}

void setIOLow(void)
{
    GPIOD->BSRR = (1 << (PIN_PD00 + 16));
}

void initPD1(void)
{
    GPIOD->MODER &= ~(3 << (PIN_PD01 * 2));
    GPIOD->MODER |=  (1 << (PIN_PD01 * 2));
    GPIOD->OTYPER &= ~(1 << PIN_PD01);
    GPIOD->BSRR = (1 << PIN_PD01);
}

void initPD0(void)
{
    GPIOD->MODER &= ~(3 << (PIN_PD00 * 2));
    GPIOD->MODER |=  (1 << (PIN_PD00 * 2));
    GPIOD->OTYPER |= (1 << PIN_PD00);
    setIOHigh();
}

void startConversion(void)
{
    if (reset())
    {
        writeByte(SKIP_ROM_COMMAND);
        writeByte(CONVERT_T_COMMAND);

        GPIOD->OTYPER &= ~(1 << PIN_PD00);  // Push-Pull
        GPIOD->BSRR = (1 << PIN_PD00);      // High
        sleep(750000);

        GPIOD->OTYPER |= (1 << PIN_PD00);   // Open-Drain
        setIOHigh();
    }
}

int16_t rawToTemp_x16(uint8_t *scratchpad, uint8_t family_code)
{
    if (family_code == FAMILY_DS18B20)
    {
        int16_t raw = (scratchpad[1] << 8) | scratchpad[0];
        return raw;
    }
    else if (family_code == FAMILY_DS18S20)
    {
        int16_t raw = (int8_t)scratchpad[0];
        return raw * 8;
    }
    return INT16_MIN;
}

int16_t readTemperature(uint8_t *rom_id)
{
    if (!reset()) return INT16_MIN;

    writeByte(MATCH_ROM_COMMAND);
    for (int i = 0; i < 8; i++)
    {
        writeByte(rom_id[i]);
    }

    writeByte(READ_SCRATCHPAD);

    uint8_t scratchpad[9];
    for (int i = 0; i < 9; i++)
    {
        scratchpad[i] = readByte();
    }

    if (check_crc(scratchpad, 8) != scratchpad[8]) return INT16_MIN;

    return rawToTemp_x16(scratchpad, rom_id[0]);
}

void displayTemperatures(void)
{
    uint8_t sensors[4][8] = {
        {0x28, 0x29, 0x7C, 0x54, 0x0F, 0x00, 0x00, 0xFB},
        {0x28, 0x09, 0x2A, 0x87, 0x0D, 0x00, 0x00, 0x82},
        {0x28, 0x96, 0x7D, 0x54, 0x0F, 0x00, 0x00, 0x15},
        {0x28, 0x5A, 0x42, 0x88, 0x0D, 0x00, 0x00, 0x40}
    };

    
    lcdGotoXY(0, 0);

    startConversion();

    for (int s = 0; s < 4; s++)
    {
        int16_t temp = readTemperature(sensors[s]);
        char buf[32];

        if (temp == INT16_MIN)
        {
            snprintf(buf, sizeof(buf), "S%d: FEHLER\n", s + 1);
        }
        else
        {
            int16_t ganz     = temp / 16;
            int16_t rest     = temp % 16;
            if (rest < 0) rest = -rest;
            uint16_t nachkomma = (uint16_t)rest * 625;
            snprintf(buf, sizeof(buf), "S%d: %d.%04d C\n", s + 1, ganz, nachkomma);
        }

        lcdPrintlnS(buf);
    }
}