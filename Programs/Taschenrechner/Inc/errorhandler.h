/**
 ******************************************************************************
 * @file    errohandler.h
 * @author  Timo Hinrichs, Emre Hakli
 * @brief   Funktionen zum behandeln von Fehlern auf dem Taschenrechner
 ******************************************************************************
 */

#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H


#define STACK_OVERFLOW -99
#define STACK_UNDERFLOW -9
#define MATH_FAIL -1
#define OTHER_OPERATIONFAIL -2
#define NULL_DIV -4
#define SWP_ERROR -3
#define SUCCESS 0
#define ARITHMETIC_OVERFLOW -5
#define ARITHMETIC_UNDERFLOW -6

/**
* @brief Gibt einen Statusfehler auf dem Screen aus und wartet, bis der Clear Knopf auf dem LCD-Screen gedrückt wird.
* @param status Der Statusfehler der auf dem Screen ausgegeben wird.
* @retval None
*/
void handleError(int status);

#endif /* ERRORHANDLER_H */