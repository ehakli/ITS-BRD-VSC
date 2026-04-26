/**
 ******************************************************************************
 * @file    operation.h
 * @author  Timo Hinrichs, Emre Hakli
 * @brief   Zentrale arithmetischen/stack-Operationen für den RTN-Taschenrechner
 ******************************************************************************
 */

#ifndef OPERATION_H
#define OPERATION_H

#define INT_MAXVALUE 2147483647
#define INT_MINVALUE -2147483648

#include "token.h"
#include <stdlib.h>
#include "stack.h"
#include <stdbool.h>

/**
* @brief Konvertiert per Modulo-Division einen Integer-Wert in ein Char-Array.
* @param num, str Die zu konvertierende Nummer, und der Zielstring in den geschrieben wird.
* @retval Fehlercode
*/
int intToString(int num, char *str);

/**
* @brief Nimmt zwei Werte vom Stack und legt deren Summe wieder auf dem Stack ab.
* @param stack
* @retval Fehlercode
*/
int add(Stack *stack);

/**
* @brief Nimmt zwei Werte vom Stack, subtrahiert den ersten (oberen) Wert vom zweiten und legt das Ergebnis wieder auf dem Stack ab.
* @param stack
* @retval Fehlercode
*/
int sub(Stack *stack);

/**
* @brief Nimmt zwei Werte vom Stack und legt deren Produkt wieder auf dem Stack ab.
* @param stack
* @retval Fehlercode
*/
int mul(Stack *stack);

/**
* @brief Nimmt zwei Werte vom Stack, teilt den zweiten Wert durch den ersten (ganzzahlige Division) und legt das Ergebnis wieder auf dem Stack ab.
* @param stack
* @retval Fehlercode
*/
int divi(Stack *stack);

/**
* @brief Druckt den obersten Wert des Stacks aus, ohne dass der Stack verändert wird.
* @param stack
* @retval Fehlercode
*/
int printtop(Stack *stack);

/**
* @brief Druckt den gesamten Stack aus, ohne dass der Stack verändert wird.
* @param stack
* @retval Fehlercode
*/
int print_all(Stack *stack);

/**
* @brief Dupliziert den obersten Eintrag des Stacks.
* @param stack
* @retval Fehlercode
*/
int duplicate(Stack *stack);

/**
* @brief Vertauscht die Reihenfolge der beiden obersten Einträge des Stacks.
* @param stack
* @retval Fehlercode
*/
int swap(Stack *stack);

/**
* @brief Wandelt eine Zahl in einen String um und gibt diesen auf dem LCD Screen aus.
* @param int Nummer
* @retval none
*/
void convertAndPrint(int number);

#endif /* OPERATION_H */