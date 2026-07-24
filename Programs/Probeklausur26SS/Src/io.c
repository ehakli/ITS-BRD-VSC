/**
 ******************************************************************************
 * @file    io.c
 *
 * @date    25. Juli 2024
 * @brief   Template der io.c für die Laborklausur GS SoSe 2024
 *
 * @author  
 *
 ******************************************************************************
 */

#include "main.h"
#include <stdbool.h>

bool getButton(int n){
    
    return !(GPIOF->IDR & 1 << n);
}


void setLEDs(bool* leds){

    for(int i = 0; i < 8; i++)
    {
        if(leds[i] == true)
        {
            GPIOD->BSRR = 1 << i; 
        }
        else 
        {
            GPIOD->BSRR = (1 << (i + 16));
        }
    }
}

// EOF