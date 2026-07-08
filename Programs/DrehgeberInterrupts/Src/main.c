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
#include "interrupts.h"


static int oldPhaseCounter = 0;
static int newPhaseCounter;
static double currTime;
static double lastTime;
static Phase oldPhase = PHASE_B;
// static Phase newPhase;
static double velocity;
static double angle;
static int status;

volatile uint32_t isr_timestamp = 0; // neu


void readSnapshot(int* ret_count, uint32_t *ret_time, char *ret_char)
{
    int cnt1, cnt2;
    uint32_t time1, time2;
    char dir1, dir2; 

    do {
      time1 = isr_timestamp;
      cnt1 = fsm_get_counter();
      dir1 = fsm_get_direction();

      time2 = isr_timestamp;
      cnt2 = fsm_get_counter();
      dir2 = fsm_get_direction();

    
    } while((cnt1 != cnt2) || (time1 != time2) || (dir1 != dir2));

    *ret_count = cnt1;
    *ret_time = time1;
    *ret_char = dir1;
    
}



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

  isr_timestamp = getTimeStamp();
  lastTime = isr_timestamp; // new

}


void initIOMODER(void) // erstmal bits an der stelle clearen, dann schreiben
{
  GPIOE->MODER = (GPIOE->MODER & ~MODER_MASK_PIN_7) | MODER_OUT_PIN_7;
  GPIOE->MODER = (GPIOE->MODER & ~MODER_MASK_PIN_6) | MODER_OUT_PIN_6; 
  GPIOE->MODER = (GPIOE->MODER & ~MODER_MASK_PIN_5) | MODER_OUT_PIN_5;  

  GPIOD->MODER = (GPIOD->MODER & ~MODER_MASK_PIND) | MODER_OUT_PIND; // counter

  GPIOE->MODER = (GPIOE->MODER & ~MODER_MASK_PIN_1) | MODER_OUT_PIN_1; // signalLED
}

int main(void) 
{

  initITSboard();
  GUI_init(DEFAULT_BRIGHTNESS);
  TP_Init(false);
  initIOMODER();
  initTimer();
  initInterruptsRouting();


  lastTime = getTimeStamp();

  int counter;
  uint32_t time;
  char direction;

  while (1) 
  {
    readSnapshot(&counter, &time, &direction);
    
    if (fsm_get_direction() == 'e') 
    {
      NVIC_DisableIRQ(EXTI0_IRQn);
      NVIC_DisableIRQ(EXTI1_IRQn);

      handleError();

      NVIC_EnableIRQ(EXTI0_IRQn);
      NVIC_EnableIRQ(EXTI1_IRQn);
    } 
    else 
    {

      double deltaTime = (currTime - lastTime) / TICKS_PER_SEC;

      if (counter != oldPhaseCounter) 
      { //inputs verarbeiten

			  velocity = getVelocity((counter - oldPhaseCounter), deltaTime);
        angle = calculateAngle(counter);

        prepareAngleBuffer(angle); //für prints vorbereiten
        prepareVelocityBuffer(velocity);

      oldPhaseCounter = counter;
      lastTime = currTime;
		}

      //outputs 
      switch (status) 
    {
      case 'i': clearDirectionLEDs(); break;
      case 'f': clearDirectionLEDs(); setForwardLED(); break;
      case 'b': clearDirectionLEDs(); setBackwardLED(); break;
      }
    }

    setStepLEDs(counter);

    signalHigh();
    processLCDUpdate();
    signalLow ();
  }
}

// EOF
