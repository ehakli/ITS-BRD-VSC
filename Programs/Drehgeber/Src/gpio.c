
#include <stdint.h>
#include <stdbool.h>
#include "gpio.h"
#include "stm32f4xx_hal.h"


void setForwardLED() // d23
{
    GPIOE->BSRR = (BSRR_MASK_PIN_7);
}

void setBackwardLED() // d22
{
    GPIOE->BSRR = (BSRR_MASK_PIN_6);
}

void setErrorLED() // d21
{
    GPIOE->BSRR = (BSRR_MASK_PIN_5);
}

void signalHigh() // für oszi
{
    GPIOE->BSRR = (BSRR_MASK_PIN_1_HIGH);
}

void signalLow()
{
    GPIOE->BSRR = (BSRR_MASK_PIN_1_LOW);
}

void setStepLEDs(int8_t counter)
{
    GPIOD->BSRR = counter;
}

bool isErrorButtonPressed() // s5
{
    return !(GPIOF->IDR & IDR_MASK_PIN_5);
}

Phase readCurrentPhase()
{
    return GPIOF->IDR & 0x03U;
}

void clearDirectionLEDs(void) 
{
    GPIOE->BSRR = (BSRR_MASK_PIN_7 << 16) | (BSRR_MASK_PIN_6 << 16) | (BSRR_MASK_PIN_5 << 16); 
}