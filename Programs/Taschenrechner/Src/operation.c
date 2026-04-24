#include "token.h"
#include <stdlib.h>
#include "stack.h"
#include <stdbool.h>
#include "errorhandler.h"
#include "display.h"
#include "operation.h"

int add(Stack *stack)
{
    int val1, val2;

    int status = pop(stack, &val1);
    if(status != SUCCESS) return status; 

	status = pop(stack, &val2);
    if(status != SUCCESS) return status; 
    
    push(val1 + val2, stack);

    return 0;

}

int sub(Stack *stack)
{
     int val1, val2;

    int status = pop(stack, &val1);
    if(status != SUCCESS) return status; 

	status = pop(stack, &val2);
    if(status != SUCCESS) return status; 
    
    push(val1 - val2, stack);

    return 0;
}

int mul(Stack *stack)
{
    int val1, val2;

    int status = pop(stack, &val1);
    if(status != SUCCESS) return status; 

	status = pop(stack, &val2);
    if(status != SUCCESS) return status; 
    
    push(val1 * val2, stack);

    return 0;
}

int divi(Stack *stack)
{
    int val1, val2;

    int status = pop(stack, &val1);
    if(status != SUCCESS) return status; 

	status = pop(stack, &val2);
    if(status != SUCCESS) return status; 
    
    push(val2 / val1, stack);

    return 0;
}

int printtop(Stack *stack)
{
    if(stack->sp == 0)
	{
		return STACK_UNDERFLOW;
	}

	else 
	{
        int val1;
		int status = peek(stack, &val1);
        if(status != SUCCESS) return status;

		convertAndPrint(val1);
	}

    return SUCCESS;
}

int print_all(Stack *stack)
{
    if(stack->sp < 1)
    {
        return STACK_UNDERFLOW;
    }

    for(int i = 0; i < stack->sp; i++)
    {
        int num = stack->arr[i];
        convertAndPrint(num);
    }

    return SUCCESS;
}

int duplicate(Stack *stack)
{
    int val1;
    int status = peek(stack, &val1);
    if(status != SUCCESS) return status;

    status = push(val1, stack);
    if(status != SUCCESS) return status;

    return 0;
}

int swap(Stack *stack)
{
    int val1, val2;

    if(stack->sp < 2)
	{
		return SWP_ERROR;	
	}
	else 
	{
		pop(stack, &val1);
		pop(stack, &val2);
					
		push(val1, stack);
		push(val2, stack);
	}

    return 0;
}



int reverseString(char *str)
{
    int head = 0;
    int tail = 0;

    while(str[tail] != '\0') {tail++;} //length
    tail--; //eins vor zeilenumbruch

    while (head < tail)
    {
        char temp = str[head];
        str[head] = str[tail];
        str[tail] = temp;

        head++;
        tail--;
    }

    return 0;
}

int intToString(int num, char *str)
{
    int i = 0;
    bool isNegative = false;

    if(num == 0)
    {
        str[i] = '0';
        str[i+1] = '\0';
        return 0;
    }

    if(num < 0) {isNegative = true;}

    long long tempNum;

    if (num < 0)
    {
        tempNum = -(long long)num;
    }
    else
    {
        tempNum = (long long)num; //muss eigentlich bei positivem fall kein ll sein, aber ist mehr consistent im code
    }

    while (tempNum > 0)
    {
        str[i++] = (tempNum % 10) + '0';
        tempNum /= 10; //next digit
    }

    if(isNegative)
    {
        str[i++] = '-';
    }

    reverseString(str);

    return 0;
}

void convertAndPrint(int number)
{
	char print[12];
	intToString(number, print);
	printStdout(print);
    printStdout("\n");
}