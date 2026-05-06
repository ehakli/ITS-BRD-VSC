


#include <stdint.h>
#include <stdbool.h>
#include "gpio.h"
#include "stm32f4xx_hal.h"

void setLED(int pos)
{

}

void setForwardLED() // d23
{
    GPIOD->BSRR = (0x1 << FORWARD_LED_POS);
}

void setBackwardLED() // d22
{
    GPIOD->BSRR = (0x1 << BACKWARD_LED_POS);
}

void setErrorLED() // d21
{
    GPIOD->BSRR = (0x1 << ERROR_LED_POS);
}

void toggleSignal() // für oszi
{

}

uint32_t counter;

void setStepLEDs()
{

}

bool isErrorButtonPressed() // s5
{
    return !(GPIOF->IDR & IDR_MASK_PIN_5);
}

