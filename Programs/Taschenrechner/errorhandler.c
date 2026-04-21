#include <stdbool.h>
#include "token.h"
#include "scanner.h"




void printErrorMessage(void)
{

}


void handleError(void)
{
    bool ErrorHandled;

    printErrorMessage(); //einmal vor der Loop


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