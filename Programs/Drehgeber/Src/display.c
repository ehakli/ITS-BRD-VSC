#include "display.h"
#include "lcd.h"
#include <stdio.h>

static char bufferArr[32];
static int bufferIndex = -1;


void display_init(void) /*schreibt den Standart text aufs Display der konstant so bleibt*/
{
    lcdSetFont(16);
    lcdGotoXY(0,0);
    lcdPrintS("aktueller Grad des Winkels: ");
    lcdGotoXY(0,60);
    lcdPrintS("Geschwindikeit: ");
}

void display_update(double winkel, double Geschwindikeit) /* aktuallisiert den Winkel und die Geschwindigkeit*/
{
    lcdGotoXY(0,30);
    lcdPrintInt((int)winkel);
    lcdGotoXY(0,90);
    lcdPrintInt((int)Geschwindikeit);
}

void prepareLCDUpdate(double angle, double velocity)
{
    snprintf(bufferArr, sizeof(bufferArr), "a:%.1f v:%.1f", angle, velocity);
    bufferIndex = 0;
}

void processLCDUpdate(void)
{
    if bufferIndex > 0 && bufferArr[bufferIndex != '\0']
    {
        lcdGotoXY(startX + bufferIndex, startY)
        lcdprintC();
        bufferIndex++;
    }
    else bufferIndex = -1; // all done
}