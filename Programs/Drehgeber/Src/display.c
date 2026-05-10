#include "display.h"
#include "lcd.h"
#include <stdio.h>

static char bufferArrAngle[16];
static int bufferIndexAngle = -1;

static char bufferArrVelocity[16];
static int bufferIndexVelocity = -1;

void prepareAngleBuffer(double angle)
{
    snprintf(bufferArrAngle, sizeof(bufferArrAngle), "A:%.3f", angle); //convert to string
    bufferIndexAngle = 0; 
}

void prepareVelocityBuffer(double velocity)
{
    snprintf(bufferArrVelocity, sizeof(bufferArrVelocity), "V:%.3f", velocity);
    bufferIndexVelocity = 0;
}

void processLCDUpdate(void)
{
    if(bufferIndexAngle >= 0 && bufferArrAngle[bufferIndexAngle] != '\0')
    {
        lcdGotoXY(ANGLEX + bufferIndexAngle, ANGLEY); //step for step, jede einzelne Zahl.
        lcdPrintC(bufferArrAngle[bufferIndexAngle]);
        bufferIndexAngle++;
    }
    else if(bufferIndexVelocity >= 0 && bufferArrVelocity[bufferIndexVelocity] != '\0')
    {
        lcdGotoXY(VELOCITYX + bufferIndexVelocity, VELOCITY_Y); 
        lcdPrintC(bufferArrVelocity[bufferIndexVelocity]);
        bufferIndexVelocity++;
    }
    else
    {
        bufferIndexAngle = -1; 
        bufferIndexVelocity = -1; // all done
    } 
}

