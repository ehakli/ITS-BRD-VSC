/**
 ******************************************************************************
 * @file    gpio.h
 * @author  Timo Hinrichs, Emre Hakli
 * @brief   Wichtige Definitionen und Methoden zum Ansteuern der IO für den Drehgeber auf dem ITS-Board
 ******************************************************************************
 */



#include "testsoftware.h"
#include <stdbool.h>
#include <stdint.h>

#ifndef GPIO_H
#define GPIO_H

//input
#define IDR_MASK_PIN_5 (0x01U << 5)


//Jeweiligen Bits im Moder-Register
#define MODER_MASK_PIN_7 (0x03U << (2*7))
#define MODER_MASK_PIN_6 (0x03U << (2*6))
#define MODER_MASK_PIN_5 (0x03U << (2*5))
#define MODER_MASK_PIN_1 (0x03U << (2*1))


//Output Masks
#define BSRR_MASK_PIN_7 (0x01U << 7)
#define BSRR_MASK_PIN_6 (0x01U << 6)
#define BSRR_MASK_PIN_5 (0x01U << 5)
#define BSRR_MASK_PIN_1_LOW (0x01U << (1 + 16))
#define BSRR_MASK_PIN_1_HIGH (0x01U << 1)


//Moder Register Konfigurierung als Output
#define MODER_OUT_PIN_7 (0x01U << (2*7))
#define MODER_OUT_PIN_6 (0x01U << (2*6))
#define MODER_OUT_PIN_5 (0x01U << (2*5))
#define MODER_OUT_PIN_1 (0x01U << (2*1))


#define BSRR_RESET_SHIFT 16

//Für Counter LEDs
#define MODER_MASK_PIND 0x0000FFFFU // nur d8-d15
#define MODER_OUT_PIND 0x00005555U // 8*01 in Hex

typedef enum {
    PHASE_A = 0x0,
    PHASE_B = 0x2,
    PHASE_C = 0x3,
    PHASE_D = 0x1
} Phase;

/** 
********************************************************************************
* @brief  Schaltet LED für den Zustand "Vorwärts" an (D23)
* @param none 
* @retval void
*/
void setForwardLED();

/** 
********************************************************************************
* @brief  Schaltet LED für den Zustand "Rückwärts" an (D22)
* @param none 
* @retval void
*/
void setBackwardLED();

/** 
********************************************************************************
* @brief  Schaltet LED für den Zustand "Fehler" an (D21)
* @param none 
* @retval void
*/
void setErrorLED();

/** 
********************************************************************************
* @brief  Gibt die Anzahl der Schritte binär auf den LEDs D8-D15 aus.
* @param counter Anzahl von Schritten
* @retval void
*/
void setStepLEDs(int8_t counter);

/** 
********************************************************************************
* @brief  Prüft, ob die Fehler-Zurücksetz Taste betätigt wird. (S5)
* @param none 
* @retval bool 
*/
bool isErrorButtonPressed();

/** 
********************************************************************************
* @brief  Liest aus den Input Ports (PF0, PF1) die Kanäle des Drehgebers.
* @param none 
* @retval Phase jetzige Phase.
*/
Phase readCurrentPhase();

/** 
********************************************************************************
* @brief  Schaltet die Status LEDs aus.
* @param none 
* @retval void
*/
void clearDirectionLEDs(void);

/** 
********************************************************************************
* @brief  Setzt das Oszilloskop Signal auf low.
* @param none 
* @retval void
*/
void signalLow();

/** 
********************************************************************************
* @brief  Setzt das Oszilloskop Signal auf high.
* @param none 
* @retval void
*/
void signalHigh();


#endif /* GPIO_H */
// EOF
