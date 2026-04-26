/**
  ******************************************************************************
  * @file    main.c
  * @author  Timo Hinrichs, Emre Hakli
  * @brief   Vollständige Implementation für den RPN-Taschenrechner für die Aufgabe 1 des GS-Praktikums.
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/

#include "init.h"
#include "display.h"
#include "scanner.h"
#include "token.h"
#include "keypad.h"
#include "stack.h"
#include "operation.h"
#include "errorhandler.h"

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
