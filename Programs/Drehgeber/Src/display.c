#include "display.h"
#include "lcd.h"
#include <stdio.h>

static char bufferArrAngle[16];
static int bufferIndexAngle = -1;

static char bufferArrVelocity[16];
static int bufferIndexVelocity = -1;


void display_init(void) /*schreibt den Standart text aufs Display der konstant so bleibt*/
{
    lcdGotoXY(0,0);
    lcdPrintS("Winkel:\0");
    lcdGotoXY(0,1);
    lcdPrintS("Geschwindikeit:\0");
}

void prepareAngleBuffer(double angle)
{
    snprintf(bufferArrAngle, sizeof(bufferArrAngle), "A:%.3f", angle);
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
        lcdGotoXY(ANGLEX + bufferIndexAngle, ANGLEY);
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

void processLCDUpdate2(void)
{
    // Winkel-Streaming
    if(bufferIndexAngle >= 0) {
        if(bufferArrAngle[bufferIndexAngle] != '\0') {
            lcdGotoXY(ANGLEX + bufferIndexAngle, ANGLEY);
            lcdPrintC(bufferArrAngle[bufferIndexAngle]);
            bufferIndexAngle++;
        } else {
            bufferIndexAngle = -1; // Nur diesen Index beenden
        }
    }
    
    // Geschwindigkeits-Streaming (läuft parallel oder danach)
    if(bufferIndexVelocity >= 0) {
        if(bufferArrVelocity[bufferIndexVelocity] != '\0') {
            lcdGotoXY(VELOCITYX + bufferIndexVelocity, VELOCITY_Y);
            lcdPrintC(bufferArrVelocity[bufferIndexVelocity]);
            bufferIndexVelocity++;
        } else {
            bufferIndexVelocity = -1; // Nur diesen Index beenden
        }
    }
}