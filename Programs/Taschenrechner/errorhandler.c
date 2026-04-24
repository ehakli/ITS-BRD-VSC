#include <stdbool.h>
#include "token.h"
#include "scanner.h"
#include "display.h"



void printErrorMessage(int status)
{
    switch(status)
    {
    case -1:
        printStdout("Error MATH_FAIL: Mathematischen-Fehler!\n");
        break;
    case -2:
        printStdout("Error OTHER_OPERATIONFAIL: Fehler bei Anweisung!\n");
        break;
    case -4: 
        printStdout("Error ZERODIFF: Es kann nicht durch 0 geteilt werden!\n");
        break;
    case -9:
        printStdout("Error STACK_UNDERFLOW: Es Muessen Zahlen zum Rechnen verwendet werden\n");
        break;
    case -99:
        printStdout("Error STACK_OVERFLOW: Zu viele Zaheln\n");
        break;
    default:
        printStdout("Error Error Error\n");
    }

    printStdout("Bitte betätige den Clear-Knopf (C) um neuzustarten.");
}


void handleError(int status)
{
    bool ErrorHandled = false;

    clearStdout();
    setErrMode();
    printErrorMessage(status); //einmal vor der Loop


    while(!ErrorHandled)
    {
        if(nextToken().tok == CLEAR)
        {
            ErrorHandled = true;
        }
    }

    clearStdout();
    setNormalMode();
}