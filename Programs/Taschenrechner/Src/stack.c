#include "token.h"
#include <stdbool.h>
#include <stdint.h>

#define STACK_SIZE 10

int32_t numStack[STACK_SIZE - 1];
int stackPointer = 0;

bool isStackFull()
{
    return sizeof(numStack) == STACK_SIZE;
}

int push(T_token token)
{
    if(!isStackFull())
    {
        stackPointer++;
        numStack[stackPointer] = token.val;
        return 0;
    }
    else {return 1;}

}

int pop()
{   
    return 0;
}

int peek()
{
    return numStack[stackPointer];
}

