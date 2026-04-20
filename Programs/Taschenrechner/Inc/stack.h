/**
  * @file stack.h
  * @author Timo Hinrichsen, Emre Hakli 
  * @date April 2026
  * @brief Stack Implementation for RTN Calculator
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





void initStack(Stack *stack);

bool isFull(Stack *stack);

bool isEmpty(Stack *stack);

int push(int value, Stack *stack);

int pop(Stack *stack, int *target);

int peek(Stack *stack,int *top);

#endif /* STACK_H */