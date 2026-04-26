/**
 ******************************************************************************
 * @file    stack.h
 * @author  Timo Hinrichs, Emre Hakli
 * @brief   Array-basierte Stack-Implementation für den RTN-Taschenrechner.
 ******************************************************************************
 */
#ifndef STACK_H
#define STACK_H

#define STACK_SIZE 10

#include "token.h"
#include <stdbool.h>
#include <stdint.h>

typedef struct {
    int arr[STACK_SIZE];
    int sp;
} Stack;




/**
* @brief Gibt an ob ein Stack voll ist.
* @param stack
* @retval boolean Ja/Nein
*/
bool isFull(Stack *stack);

/**
* @brief Gibt an ob ein Stack leer ist.
* @param stack
* @retval boolean Ja/Nein
*/
bool isEmpty(Stack *stack);

/**
* @brief Fügt dem Stack einen Wert hinzu.
* @param value, stack 
* @retval Fehlercode
*/
int push(int value, Stack *stack);

/**
* @brief Entfernt einen Wert aus dem Stack.
* @param stack, target Schreibt den Wert aus dem Stack in Targets Adresse.
* @retval Fehlercode
*/
int pop(Stack *stack, int *target);

/**
* @brief Enthüllt einen Wert aus dem Stack ohne ihn zu entfernen
* @param stack, top Schreibt den Wert aus dem Stack in tops Adresse.
* @retval Fehlercode
*/
int peek(Stack *stack, int *top);

#endif /* STACK_H */