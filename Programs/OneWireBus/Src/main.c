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
#include "timer.h"
#include "gpio.h"
#include <stdio.h>
#include "mysleep.h"
#include "search.h"


int main(void)
{
    initITSboard();
    GUI_init(DEFAULT_BRIGHTNESS);
    TP_Init(false);
    initTimer();
    initPD1();
    initPD0();

    while (1)
    {
        displayTemperatures();
        sleep(1000000);
    }
}

// EOF
