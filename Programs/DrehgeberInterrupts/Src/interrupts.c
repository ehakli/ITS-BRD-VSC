#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "timer.h"
# include "fsm.h"

extern volatile uint32_t isr_timestamp; 


void EXTI0_IRQHandler(void)
{
    signalHigh();

    uint32_t time = getTimeStamp();
    Phase phase = readCurrentPhase();

    if(EXTI->PR & (1 << 0)) // flag check
    {
        EXTI->PR = (1 << 0); //flag reset
        isr_timestamp = time;
        fsm_update(phase);
    }

    signalLow();
}

void EXTI1_IRQHandler(void)
{
    signalHigh();

    uint32_t time = getTimeStamp();
    Phase phase = readCurrentPhase();
    

    if(EXTI->PR & (1 << 1)) // flag check
    {
        EXTI->PR = (1 << 1); //flag reset
        isr_timestamp = time;
        fsm_update(phase);
    }

    signalLow();
}

void initInterruptsRouting()
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN; // Clock for GPIO Port F
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN; // System conf. Clock enable

    SYSCFG->EXTICR[0] &= ~(0x0f << (4*0)); //Remove old selection
    SYSCFG->EXTICR[0] |= 0x06 << (4*0);

    SYSCFG->EXTICR[0] &= ~(0x0f << (4*1)); //Remove old selection
    SYSCFG->EXTICR[0] |= 0x06 << (4*1);

    EXTI->RTSR |= (1 << 0) | (1 << 1); // Rising Trigger (Steigende Flanke)
    EXTI->FTSR |= (1 << 0) | (1 << 1); // Falling Trigger (Fallende Flanke)

    EXTI->IMR |= (1 << 0) | (1 << 1); // Unmask INT2

    NVIC_SetPriority(EXTI0_IRQn, 15); // Prio für pin 0
    NVIC_EnableIRQ(EXTI0_IRQn); // enable

    NVIC_SetPriority(EXTI1_IRQn, 15); // prio für pin 1
    NVIC_EnableIRQ(EXTI1_IRQn); // enable

    
}