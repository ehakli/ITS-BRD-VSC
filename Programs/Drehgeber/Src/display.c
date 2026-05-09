#include "display.h"
#include "lcd.h"

void display_init(void)
{
    lcdSetFont(16);
    lcdGotoXY(0,0);
    lcdPrintS("aktueller Grad des Winkels: ");
    lcdGotoXY(0,60);
    lcdPrintS("Geschwindikeit: ")
}

void display_update(double winkel, double Geschwindikeit)
{
    lcdGotoXY(0,30);
    lcdPrintInt((int)winkel);
    lcdGotoXY(0,90);
    lcdPrintInt((int)Geschwindikeit);
}