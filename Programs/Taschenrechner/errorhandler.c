#include <stdbool.h>
#include "token.h"
#include "scanner.h"
#include "display.h"



void printErrorMessage(int fehlercode)
{
    switch(fehlercode)
    {
    case -1:
    printStdout("Error MATH_FAIL: Mathematischen-Fehler!");
    break;
    case -2:
    printStdout("Error OTHER_OPERATIONFAIL: Fehler bei Anweisung!");
    break;
    case -4: 
    printStdout("Error ZERODIFF: Es kann nicht durch 0 geteilt werden!");
    break;
    case -9:
    printStdout("Error STACK_UNDERFLOW: Es Muessen Zahlen zum Rechnen verwendet werden");
    break;
    case -99:
    printStdout("Error STACK_OVERFLOW: Zu viele Zaheln");
    break;
    default:
    printStdout("Error Error Error");
    }
    
}


void handleError(int fehlercode);
{
    bool ErrorHandled;

    printErrorMessage(int fehlercode); //einmal vor der Loop


    while(!ErrorHandled)
    {
        if(nextToken().tok == CLEAR)
        {
            ErrorHandled = true;
        }
    }

    //clear stdout
    //clear screen
    //clear stack
    
}