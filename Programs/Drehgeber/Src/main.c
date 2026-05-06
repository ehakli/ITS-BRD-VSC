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
#include <stdio.h>
#include "gpio.h"
/*Module : 
timer.c (Zeitlesen und zeitspanne ausrechnen)
FSM.c (Phasenerkeunng, zähler und fehlerstate)
winkel.c (Winkel und Winkelgeschwindigkeit)
gpio.c (signal einlesen und leuchten ansteuern)
display.c (display ausgabe)
main.c (superloop)*/
// In discord server bit shifting gemacht
int main(void) {
    initITSboard();    // Initialisierung des ITS Boards
    GUI_init(DEFAULT_BRIGHTNESS);
    TP_Init(false);
    GPIOE->BSRR; // 
    GPIOD->BSRR; // BSRR Ersten 0-7 bits = Schreiben, die 15-23 sind ausmachen
    GPIOF->IDR; // ersten Zwei Stellen: Input vom Drehregler
    GPIOF->MODER &= ~((0x03U << (2*0)) | (0x03U << (2*1)));
    
  // Begruessungstext   
    
    // Test in Endlosschleife
    while(1) {

		setForwardLED();
		//lcdPrintInt(isErrorButtonPressed());
        // signal lesen (gpios)
        // FSM updaten
        //alle 250-500ms dann WinkelGeschwindigkeit berechnen
        //leds passend setzen
        // wenn veränderung Display aktuallisieren
        // schauen ob fehler (S6) und wenn ja löschen
    }
}

// EOF

