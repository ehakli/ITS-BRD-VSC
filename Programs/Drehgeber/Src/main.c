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
#include "angle.h"
#include "display.h"
#include "fsm.h"
/*Module : 
timer.c (Zeitlesen und zeitspanne ausrechnen)
FSM.c (Phasenerkeunng, zähler und fehlerstate)
winkel.c (Winkel und Winkelgeschwindigkeit)
gpio.c (signal einlesen und leuchten ansteuern)
display.c (display ausgabe)
main.c (superloop)*/
// In discord server bit shifting gemacht

static int stepCounter;
static int phasediff;
static int oldPhaseCounter = 0;
static int newPhaseCounter;
static double currTime;
static double lastTime;
static Phase oldPhase = PHASE_B;
static Phase newPhase;
static double velocity;
static double angle;
static int status;


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

    while(1) {
		//phasen checken, oldphase newphase implementieren
    newPhase = readCurrentPhase();
		currTime = getTimeStamp();

		uint32_t deltaTime = currTime - lastTime;

    fsm_update(newPhase);
    status = fsm_get_direction();

		if(((deltaTime > 0,25) && (oldPhase != newPhase)) || (deltaTime > 0,5))
		{
			newPhaseCounter = fsm_get_counter();
			velocity = getVelocity((newPhaseCounter - oldPhaseCounter), deltaTime);
      angle = calculateAngle(stepCounter);
			oldPhaseCounter = newPhaseCounter;
      prepareLCDUpdate(angle, velocity);
      
		}

    switch(status)
    {
      case 'i': break;
      case 'f': setForwardLED(); break;
      case 'b': setBackwardLED(); break; 
    }

    setStepLEDs(newPhaseCounter);
    // wenn geprintet werden muss 
    
    processLCDUpdate();
		

        // uint8_t status = readCurrentPhase();
		// phasediff berechnen (wenn nicht idle oder error)
        // lcdPrintInt(status);
        // signal lesen (gpios)
        // FSM updaten
        // alle 250-500ms dann WinkelGeschwindigkeit berechnen
        //leds passend setzen
        // wenn veränderung Display aktuallisieren
        // schauen ob fehler (S6) und wenn ja löschen

		lastTime = currTime;
    }
}


/** gpio einlesen
update fsm
check error
berechnungen machen, gpio outputs 

wir erstellen einen buffer, der die zahlen als charArray speichert
für prints: wir erstellen jedes mal wenn getvelocity gecalld wird, wird dieser buffer mit der neuen zahl überschrieben. wir starten bei einem iindex von 0 und geben nur einzelne
ziffern aus anstatt ganze zahlen. nach dem ausgeben von einzelnen ziffern wird der index erhöht. basierend auf dem index können die print positionen auch gemacht werden
dieses printen passiert außerhalb von unserem getVelocity block 
´ß
*/



// EOF

