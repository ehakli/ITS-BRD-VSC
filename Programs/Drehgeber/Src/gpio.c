


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

void toggleSignal() // für oszi
{

}

uint32_t counter;

void setStepLEDs(uint32_t counter)
{
    GPIOD->BSRR = counter;
}

bool isErrorButtonPressed() // s5
{
    return !(GPIOF->IDR & IDR_MASK_PIN_5);
}

Phase readCurrentPhase()
{
    // GPIOF->MODER &= ~((0x03U << (2*0)) | (0x03U << (2*1)));
    return GPIOF->IDR & 0x03U;
}