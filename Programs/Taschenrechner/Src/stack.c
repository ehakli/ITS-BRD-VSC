#include "token.h"
#include <stdbool.h>
#include <stdint.h>
#include "stack.h"



void initStack(Stack *stack)
{
    stack->sp = 0;
}

bool isFull(Stack *stack)
{
    return stack->sp == STACK_SIZE;
}

bool isEmpty(Stack *stack)
{
    return stack->sp == 0;
}

int push(int value, Stack *stack)
{
    if(!isFull(stack))
    {
        stack->arr[stack->sp] = value;
        stack->sp++;
        return 0;
    }
    else return -1;
}

int pop(Stack *stack, int *target)
{   
    if(!isEmpty(stack)) 
    {
        *target = stack->arr[stack->sp - 1];
        stack->sp--;
        return 0;
    }
    else return 1;
}

int peek(Stack *stack,int *top)
{
    if(stack->sp > 0)
    {
         *top = stack->arr[stack->sp - 1];
        return 0;
    }
    else 
    {
        return 1;
    }
}

