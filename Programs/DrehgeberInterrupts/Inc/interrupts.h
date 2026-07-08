extern volatile uint32_t isr_timestamp;

void initInterruptsRouting();
void EXTI1_IRQHandler(void);
void EXTI0_IRQHandler(void);