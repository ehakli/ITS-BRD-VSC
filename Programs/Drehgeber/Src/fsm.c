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
    return '?'; /*optimal nie*/
}

void fsm_update(int kanal_a, int kanal_b)
{
    char neue_phase = fsm_get_phase(kanal_a, kanal_b);
    if(letzte_phase == neue_phase)
    {
        /*Keine veränderung*/
    }
    else if(letzte_phase == 'a' && neue_phase == 'b')
    {
        phasen_zaehler++;
        drehrichtung = 'v';
    }
    else if(letzte_phase == 'b' && neue_phase == 'c')
    {
        phasen_zaehler++;
        drehrichtung = 'v';
    }
    else if(letzte_phase == 'c' && neue_phase == 'd')
    {
        phasen_zaehler++;
        drehrichtung = 'v'
    }
    else if(letzte_phase == 'd' && neue_phase == 'a')
    {
        phasen_zaehler++;
        drehrichtung = 'v';
    }
    else if(letzte_phase == 'b' && neue_phase == 'a')
    {
        phasen_zaehler++;
        drehrichtung = 'r';
    }
    else if(letzte_phase == 'a' && neue_phase == 'd')
    {
        phasen_zaehler++;
        drehrichtung = 'r';
    }
    else if(letzte_phase == 'd' && neue_phase =='c')
    {
        phasen_zaehler++;
        drehrichtung = 'r';
    }
    else if(letzte_phase == 'c' && neue_phase == 'b')
    {
        phasen_zaehler++;
        drehrichtung = 'r';
    }
    else
    {
        fehler = 1;
    }

    letzte_phase = neue_phase;
}

int fsm_get_zeahler(void)
{
    return phasen_zaehler;
}
int fsm_hat_fehler(void)
{
    return fehler;
}
char fsm_get_richtung(void)
{
    return drehrichtung;
}
void fsm_reset_fehler()
{
    fehler = 0;
}
void fsm_reset_zaehler()
{
    phasen_zaehler = 0; drehrichtung = '?';
}