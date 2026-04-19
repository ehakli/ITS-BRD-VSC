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
#include "display.h"
#include "scanner.h"
#include "token.h"
#include "keypad.h"
#include <stdio.h>

// To-Do:
// Tokens müssen nicht großartig behandelt werden, nur verarbeitet. Mit stdio print die fehlercodes, immer call by reference, alles 
// müsste ein int return haben um fehler codes zu haben, method für errorhandling, operationen hardcoden.
int main(void) {

	initITSboard();    // Initialisierung des ITS Boards
	initDisplay();

	GUI_init(DEFAULT_BRIGHTNESS);   // Initialisierung des LCD Boards mit Touch
	TP_Init(false);                 // Initialisierung des LCD Boards mit Touch

	makeKeyPad();

	while(1)
	{
		char c = getKeyPadInput();
		printToEchoLine(c);
	}

  /* Begruessungstext	
	lcdPrintlnS("Hallo liebes TI-Labor (c-project)");
	
	 Test in Endlosschleife
	while(1) {
		HAL_Delay(10000);
	} */
}

// EOF
