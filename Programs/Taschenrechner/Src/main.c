/**
  ******************************************************************************
  * @file    main.c
  * @author  Franz Korf
  * @brief   Kleines Testprogramm fuer neu erstelle Fonts. pommes
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
#include "stack.h"
#include "operation.h"

// To-Do:
// Tokens müssen nicht großartig behandelt werden, nur verarbeitet. Mit stdio print die fehlercodes, immer call by reference, alles 
// müsste ein int return haben um fehler codes zu haben, method für errorhandling, operationen hardcoden.

void convertAndPrint(int number)
{
	char print[12];
	intToString(number, print);
	printStdout(print);
}

// 
int main(void) {

	initITSboard();    // Initialisierung des ITS Boards
	initDisplay();
	makeKeyPad();

	Stack stack;

	while(1)
	{
		T_token currentToken = nextToken();
		int number, val1, val2, val3, status;

		switch (currentToken.tok)
		{
			case NUMBER:
				status = push(currentToken.val, &stack);
				convertAndPrint(currentToken.val);
				break;
			case PLUS: case MINUS: case MULT: case DIV:
				pop(&stack, &val1); // in eine methode zusammenfassen, dann den status direkt bei error returnen
				pop(&stack, &val2);

				status = doArithmeticOperation(val1, val2, currentToken.tok, &val3);
				push(val3, &stack); 
				break;

			case CLEAR:
				stack.sp = 0;
				break;

			case PRT:
				int print;
				peek(&stack, &print);
				convertAndPrint(print);

				

		}
	}	
}



int handleToken()
{

	return 0;
}


// EOF
