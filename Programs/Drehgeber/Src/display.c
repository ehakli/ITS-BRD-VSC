#include "display.h"
#include "lcd.h"
#include <stdio.h>

static char bufferArrAngle[16];
static int bufferIndexAngle = -1;

static char bufferArrVelocity[16];
static int bufferIndexVelocity = -1;


void display_init(void) /*schreibt den Standart text aufs Display der konstant so bleibt*/
{
    lcdSetFont(16);
    lcdGotoXY(0,0);
    lcdPrintS("aktueller Grad des Winkels:");
    lcdGotoXY(0,1);
    lcdPrintS("Geschwindikeit: ");
}

void display_update(double winkel, double Geschwindikeit) /* aktuallisiert den Winkel und die Geschwindigkeit*/
{
    lcdGotoXY(0,30);
    lcdPrintInt((int)winkel);
    lcdGotoXY(0,90);
    lcdPrintInt((int)Geschwindikeit);
}

void prepareAngleBuffer(double angle)
{
    snprintf(bufferArrAngle, sizeof(bufferArrAngle), "a:%.3f", angle);
    bufferIndexAngle = 0;
}

void prepareVelocityBuffer(double velocity)
{
    snprintf(bufferArrVelocity, sizeof(bufferArrVelocity), "v:%.3f", velocity);
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