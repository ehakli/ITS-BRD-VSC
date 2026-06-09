#include <stdint.h>
#define PIN_PD01 0x1
#define PIN_PD00 0x0


#include "stm32f429xx.h"
#include "mysleep.h"
#include "gpio.h"

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