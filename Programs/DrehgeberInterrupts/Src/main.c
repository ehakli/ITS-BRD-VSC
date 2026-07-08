#include "LCD_GUI.h"
#include "LCD_Touch.h"
#include "additionalFonts.h"
#include "angle.h"
#include "display.h"
#include "error.h"
#include "fontsFLASH.h"
#include "fsm.h"
#include "gpio.h"
#include "init.h"
#include "lcd.h"
#include "stm32f4xx_hal.h"
#include "timer.h"
#include <stdint.h>
#include <stdio.h>

static int oldPhaseCounter = 0;
static int newPhaseCounter;
static double currTime;
static double lastTime;
static Phase oldPhase = PHASE_B;
static Phase newPhase;
static double velocity;
static double angle;
static int status;

volatile uint32_t isr_timestamp = 0; // neu

void handleError()
{
  bool ErrorHandled = false;
  clearDirectionLEDs();
  setErrorLED();
  
  while(!ErrorHandled)
  {
    if(isErrorButtonPressed())
    {

      oldPhaseCounter = 0;
      newPhaseCounter = 0;
      currTime = 0;
      lastTime = 0;
      oldPhase = PHASE_B;
      velocity = 0;
      angle = 0;
      fsm_reset();
      ErrorHandled = true;
    }
  }
}
void initIOMODER(void) // erstmal bits an der stelle clearen, dann schreiben
{
  GPIOE->MODER = (GPIOE->MODER & ~MODER_MASK_PIN_7) | MODER_OUT_PIN_7;
  GPIOE->MODER = (GPIOE->MODER & ~MODER_MASK_PIN_6) | MODER_OUT_PIN_6; 
  GPIOE->MODER = (GPIOE->MODER & ~MODER_MASK_PIN_5) | MODER_OUT_PIN_5;  

  GPIOD->MODER = (GPIOD->MODER & ~MODER_MASK_PIND) | MODER_OUT_PIND; // counter

  GPIOE->MODER = (GPIOE->MODER & ~MODER_MASK_PIN_1) | MODER_OUT_PIN_1; // signalLED
}

int main(void) {
  initITSboard();
    GUI_init(DEFAULT_BRIGHTNESS);
    TP_Init(false);

    initIOMODER();
  initTimer();
  lastTime = getTimeStamp();

  while (1) 
  {
    ///inputs holen
    newPhase = readCurrentPhase();
		currTime = getTimeStamp();


    fsm_update(newPhase);
    if (fsm_get_direction() == 'e') 
    {
      handleError();
    } 
    else 
    {
    status = fsm_get_direction();
      double deltaTime = (currTime - lastTime) / TICKS_PER_SEC;

      if (((deltaTime > 0.25) && (oldPhase != newPhase)) || (deltaTime > 0.5)) 
      { //inputs verarbeiten
			newPhaseCounter = fsm_get_counter();

			velocity = getVelocity((newPhaseCounter - oldPhaseCounter), deltaTime);
        angle = calculateAngle(newPhaseCounter);

        prepareAngleBuffer(angle); //für prints vorbereiten
      prepareVelocityBuffer(velocity);

      oldPhaseCounter = newPhaseCounter;
      lastTime = currTime;
		}

      oldPhase = newPhase;

      //outputs 
      switch (status) 
    {
      case 'i':
        clearDirectionLEDs();
        break;
      case 'f':
        clearDirectionLEDs();
        setForwardLED();
        break;
      case 'b':
        clearDirectionLEDs();
        setBackwardLED();
        break;
      }
    }

    setStepLEDs(newPhaseCounter);
    signalHigh();
    processLCDUpdate();
    signalLow ();
  }
}

// EOF
