/**
  ******************************************************************************
  * @file    main.c
  * @author  Franz Korf
  * @brief   Kleines Testprogramm fuer neu erstelle Fonts.
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/

#include "stm32f4xx_hal.h"
#include "init.h"
#include "LCD_GUI.h"
#include "LCD_Touch.h"
#include "lcd.h"
#include "fontsFLASH.h"
#include "additionalFonts.h"
#include "error.h"
#include "lcd.h"
#include <stdint.h>
#include <stdio.h>
#include "gpio.h"
#include "timer.h"
/*Module : 
timer.c (Zeitlesen und zeitspanne ausrechnen)
FSM.c (Phasenerkeunng, zähler und fehlerstate)
winkel.c (Winkel und Winkelgeschwindigkeit)
gpio.c (signal einlesen und leuchten ansteuern)
display.c (display ausgabe)
main.c (superloop)*/
// In discord server bit shifting gemacht

void initIOMODER(void)
{
  GPIOE->MODER = (GPIOE->MODER & ~MODER_MASK_PIN_7) | MODER_OUT_PIN_7;
  GPIOE->MODER = (GPIOE->MODER & ~MODER_MASK_PIN_6) | MODER_OUT_PIN_6; 
  GPIOE->MODER = (GPIOE->MODER & ~MODER_MASK_PIN_5) | MODER_OUT_PIN_5;  

  GPIOD->MODER = (GPIOD->MODER & ~MODER_MASK_PIND) | MODER_OUT_PIND;

}
int main(void) {
    initITSboard();    // Initialisierung des ITS Boards
    GUI_init(DEFAULT_BRIGHTNESS);
    TP_Init(false);

    initTimer();
    initIOMODER();
    setStepLEDs(200);
    initTimer();

    while(1) {

        // uint8_t status = readCurrentPhase();
        // lcdPrintInt(status);
        // signal lesen (gpios)
        // FSM updaten
        // alle 250-500ms dann WinkelGeschwindigkeit berechnen
        //leds passend setzen
        // wenn veränderung Display aktuallisieren
        // schauen ob fehler (S6) und wenn ja löschen
    }
}

// EOF

