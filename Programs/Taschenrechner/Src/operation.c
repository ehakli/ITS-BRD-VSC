#include "token.h"
#include <stdlib.h>
#include "stack.h"
#include <stdbool.h>

int doArithmeticOperation(int val1, int val2, char operator, int* target) 
{
    switch (operator) 
    {
    case PLUS:
    *target = val1 + val2;
    break;

    case MINUS:
    *target = val1 - val2;
    break;

    case MULT:
    *target = val1 * val2;

    case DIV:
    *target = val2 / val2;

    default:
    return -1;
    }   

    return 0;
}

int doStackOperation (Stack *stack, char operator)
{

    switch(operator)
    {
        case PRT:

        case PRT_ALL:

        case CLEAR:

        case DOUBLE:

        case SWAP: 
        
        default:

        return 0;
    }

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