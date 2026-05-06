#include <stdbool.h>

#ifndef GPIO_H
#define GPIO_H

#define FORWARD_LED_POS 16
#define BACKWARD_LED_POS 15
#define ERROR_LED_POS 14
#define IDR_MASK_PIN_5 (0x01U << 5)


typedef enum {
    PhaseA = 0,
    PhaseB = 2,
    PhaseC = 3,
    PhaseD = 1
} Phase;

void setForwardLED();
bool isErrorButtonPressed();

#endif /* GPIO_H */
// EOF
