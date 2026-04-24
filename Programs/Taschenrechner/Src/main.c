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
#include "errorhandler.h"

// To-Do:
// Tokens müssen nicht großartig behandelt werden, nur verarbeitet. Mit stdio print die fehlercodes, immer call by reference, alles 
// müsste ein int return haben um fehler codes zu haben, method für errorhandling, operationen hardcoden.



// 
int main(void) {

	initITSboard();    // Initialisierung des ITS Boards
	initDisplay();
	makeKeyPad();

	Stack stack;

	while(1)
	{
		T_token currentToken = nextToken();
		clearStdout();
		
		int status = 0;

		switch (currentToken.tok)
		{
			case NUMBER:
				status = push(currentToken.val, &stack);
				break;

			case PLUS:
				status = add(&stack);
				break;

			case MINUS: 
				status = sub(&stack);
				break;

			case MULT: 
				status = mul(&stack);
				break;

			case DIV:
				status = divi(&stack);
				break;


			case CLEAR:
				stack.sp = 0;
				break;

			case PRT:
				status = printtop(&stack);
				break;

			case SWAP:
				status = swap(&stack);
				break;

			case DOUBLE:
				status = duplicate(&stack);
				break;

			case PRT_ALL:
				status = print_all(&stack);
				break;

		}
		if (status != SUCCESS)
		{
			handleError(status);
		}
	}	
}




// EOF
