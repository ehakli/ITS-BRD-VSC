#include <stdint.h>
#define PIN_PD01 0x1
#define PIN_PD00 0x0
#define READ_ROM_COMMAND 0x33
#define CRC_LENGTH 7
#define CRC_POS 7

#include "stm32f429xx.h"
#include "mysleep.h"
#include "gpio.h"

uint8_t romdata[8];


void readRom()
{
    if(reset() == 1)
    {
        writeByte(READ_ROM_COMMAND);

        for(int i = 0; i < 8; i++)
        {
            romdata[i] = readByte();
        }

        uint8_t calculateed_crc = check_crc(romdata, sizeof(romdata));

        if(calculateed_crc == romdata[CRC_POS])
        {
            //print stuff crc richtig, family code 
        }
        else
        {
            // print stuff crc falsch
        }
    }
    else
    {
        // print stuff kein sensor
    }
}

uint8_t check_crc(uint8_t *data, uint8_t len)
{
    uint8_t crc = 0;

    for(int i = 0; i < len; i++)
    {
        uint8_t byte = data[i];
        for(int j = 0; j < 8; j++)
        {
            uint8_t calculated = (crc ^ byte) & 0x01;

            crc = crc >> 1;

            if(calculated)
            {
                crc ^= 0x8C;
            }

            byte = byte >> 1;
        }
    }

    return crc;
}

uint8_t readByte()
{
    uint8_t value = 0;

    for(int i=0; i<8; i++)
    {
        uint8_t bit = readBit();

        value |= (bit << i);
    }

    return value;
}


void writeByte(uint8_t byte)
{
    for(int i=0; i<8; i++)
    {
        uint8_t bit = (byte >> i) & 1;

        if(bit == 1)
        {
            writeOne();
        }
        else
        {
            writeZero();
        }
    }
}


uint8_t reset()
{
    setIOLow();
    sleep(480);
    setIOHigh();
    sleep(70);

    uint8_t pulse = 0;
    uint8_t status = GPIOD->IDR;

    if(((status) & (1 << PIN_PD00)) == 0)
    {
        pulse = 1;
    }

    sleep(410);
    return pulse;
}

uint8_t readBit()
{
    uint8_t bit = 0;

    setIOLow();
    sleep(6);
    setIOHigh();
    sleep(9);

    if(GPIOD->IDR & (1 << PIN_PD00))
    {
        bit = 1;
    }

    sleep(55);

    return bit;
}

void writeZero()
{
    setIOLow();
    sleep(60);
    setIOHigh();
    sleep(10);
}

void writeOne()
{
    setIOLow();
    sleep(6);
    setIOHigh();
    sleep(64);

}

void setIOHigh()
{
    GPIOD->BSRR = (1 << PIN_PD00);
}

void setIOLow()
{
    GPIOD->BSRR = (1 << (PIN_PD00+16));
}

void initPD1()
{
    GPIOD->MODER &= ~(3 << (PIN_PD01 * 2)); //Reset
    GPIOD->MODER |=  (1 << (PIN_PD01 * 2)); //set output
    GPIOD->OTYPER &= ~(1 << PIN_PD01); //set push pull
    GPIOD->BSRR = (1 << PIN_PD01); // set high - wird nicht geändert
}

void initPD0()
{
    GPIOD->MODER &= ~(3 << (PIN_PD00 * 2)); //Reset
    GPIOD->MODER |=  (1 << (PIN_PD00 * 2)); //set output
    GPIOD->OTYPER |= (1 << PIN_PD00); //set open drain
    setIOHigh(); // auf hoch ziehen, basically anfangszustand
}