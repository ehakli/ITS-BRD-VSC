#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

void initInterruptsRouting()
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN; // Clock for GPIO Port F
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN; // System conf. Clock enable
    
}