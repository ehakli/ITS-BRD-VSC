#include <stdbool.h>
#include "errorhandler.h"
#include "token.h"
#include "scanner.h"
#include "display.h"



void printErrorMessage(int status)
{
    switch(status)
    {
    case -1:
        printStdout("Error MATH_FAIL: Mathematischen-Fehler!\0");
        break;
    case -2:
        printStdout("Error OTHER_OPERATIONFAIL: Fehler bei Anweisung!\0");
        break;
    case -4: 
        printStdout("Error ZERODIFF: Es kann nicht durch 0 geteilt werden!\0");
        break;
    case -9:
        printStdout("Error STACK_UNDERFLOW: Es Muessen Zahlen zum Rechnen verwendet werden\0");
        break;
    case -99:
        printStdout("Error STACK_OVERFLOW: Zu viele Zahlen\0");
        break;
    case -5:
        printStdout("Error ARITHMETIC_OVERFLOW: Bereichsueberschreitung!");
        break;
    case -6:
        printStdout("Error: ARITHMETIC_UNDERFLOW: Bereichsueberschreitung!");
    default:
        printStdout("Error Error Error\0");
    }
    printStdout("\n\0");
    printStdout("Bitte betaetige den Clear-Knopf (C) um neuzustarten.\0");


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