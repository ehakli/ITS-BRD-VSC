#include "display.h"
#include "lcd.h"

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