#include "errorhandler.h"
#include "token.h"
#include <stdbool.h>
#include <stdint.h>
#include "stack.h"


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
        return SUCCESS;
    }
    else return STACK_OVERFLOW;
}

int pop(Stack *stack, int *target)
{   
    if(!isEmpty(stack)) 
    {
        *target = stack->arr[stack->sp - 1];
        stack->sp--;
        return SUCCESS;
    }
    else return STACK_UNDERFLOW;
}

int peek(Stack *stack,int *top)
{
    if(stack->sp > 0)
    {
         *top = stack->arr[stack->sp - 1];
        return SUCCESS;
    }
    else 
    {
        return STACK_UNDERFLOW;
    }
}

