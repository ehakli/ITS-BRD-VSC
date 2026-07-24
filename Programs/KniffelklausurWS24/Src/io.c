#include "error.h"
#include <stdint.h>
#include "stm32f4xx_hal.h"
#include <stdbool.h>

void setLEDs(uint8_t noLeds)
{
    // 1. Fehlerabfrage: Nur wenn GRÖßER 16
    if(noLeds > 16)
    {
        Error_Handler();
        return; 
    }

    GPIOD->BSRR = (0xFF << 16);
    GPIOE->BSRR = (0xFF << 16);

    for(int i = 0; i < noLeds; i++) 
    {
        if(i < 8)
        {
            GPIOD->BSRR = (1 << i); 
        }
        else 
        {
            GPIOE->BSRR = (1 << (i - 8)); 
        }
    }
}

bool buttonPressed(uint8_t button)
{
    if(button > 7)
    {
        Error_Handler();
    }
    else 
    {
        return !(GPIOF->IDR & 1 << button);
    }
}


// EOF