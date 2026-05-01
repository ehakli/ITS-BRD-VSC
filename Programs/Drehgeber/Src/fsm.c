static char letzte_phase = b; /*Start*/
static int phasen_zaehler = 0;
static int fehler = 0;
static char drehrichtung = ?; /*indikator für die richtung startet bei keinem*/

char fsm_gib_phase(char a, char b) 
{
    if(a == 0 && b == 0) return a;
    if(a == 1 && b == 0) return b;
    if(a == 1 && b == 1) return c;
    if(a == 0 && b == 1) return d;
}