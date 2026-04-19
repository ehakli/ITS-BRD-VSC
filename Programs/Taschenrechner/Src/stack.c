#include "token.h"
#include <stdbool.h>
#include <stdint.h>


#define STACK_SIZE 10

typedef struct {
    int arr[STACK_SIZE];
    int sp;
} Stack;

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

int push(T_token token, Stack *stack)
{
    if(!isFull(stack))
    {
        stack->arr[stack->sp] = token.value;
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

