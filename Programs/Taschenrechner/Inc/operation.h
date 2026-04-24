#include "token.h"
#include <stdlib.h>
#include "stack.h"
#include <stdbool.h>

int doArithmeticOperation(int val1, int val2, char operator, int * target);

int doStackOperation (Stack *stack, char operator);

int reverseString(char *str);

int intToString(int num, char *str);

int add(Stack *stack);

int sub(Stack *stack);

int mul(Stack *stack);

int divi(Stack *stack);
