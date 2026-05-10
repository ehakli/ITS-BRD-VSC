#include "testsoftware.h"
#include <stdbool.h>
#include <stdint.h>

#ifndef GPIO_H
#define GPIO_H

#define IDR_MASK_PIN_5 (0x01U << 5)

#define MODER_MASK_PIN_7 (0x03U << (2*7))
#define MODER_MASK_PIN_6 (0x03U << (2*6))
#define MODER_MASK_PIN_5 (0x03U << (2*5))

#define BSRR_MASK_PIN_7 (0x01U << 7)
#define BSRR_MASK_PIN_6 (0x01U << 6)
#define BSRR_MASK_PIN_5 (0x01U << 5)

#define MODER_OUT_PIN_7 (0x01U << (2*7))
#define MODER_OUT_PIN_6 (0x01U << (2*6))
#define MODER_OUT_PIN_5 (0x01U << (2*5))

#define BSRR_RESET_SHIFT 16

#define MODER_MASK_PIND 0x0000FFFFU // nur d8-d15
#define MODER_OUT_PIND 0x00005555U // 8*01 in Hex

#define SCOPE_PIN 4

typedef enum {
    PHASE_A = 0x0,
    PHASE_B = 0x2,
    PHASE_C = 0x3,
    PHASE_D = 0x1
} Phase;

void setForwardLED();
void setBackwardLED();
void setErrorLED();
void setStepLEDs(int8_t counter);
bool isErrorButtonPressed();
Phase readCurrentPhase();
void clearDirectionLEDs(void);
void toggleSignal();
#endif /* GPIO_H */
// EOF
