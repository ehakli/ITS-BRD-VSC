#include "gpio.h"
#include "fsm.h"

static char last_phase = PHASE_B; /*Start*/
static int phasen_counter = 0;
static int error = 0;
static char direction  = 'i'; /*indikator für die richtung startet bei i = idle*/


void fsm_update(Phase newphase) /*aktuallisiert die Phase*/
{
    Phase new_phase = newphase; // 🐐
    if(last_phase == new_phase)
    {
        direction = 'i';
    }
    else if(last_phase == PHASE_A && new_phase == PHASE_B)
    {
        phasen_counter++;
        direction = 'f';
    }
    else if(last_phase == PHASE_B && new_phase == PHASE_C)
    {
        phasen_counter++;
        direction = 'f';
    }
    else if(last_phase == PHASE_C && new_phase == PHASE_D)
    {
        phasen_counter++;
        direction = 'f'; 
    }
    else if(last_phase == PHASE_D && new_phase == PHASE_A)
    {
        phasen_counter++;
        direction = 'f';
    }
    else if(last_phase == PHASE_B && new_phase == PHASE_A)
    {
        phasen_counter--;
        direction = 'b';
    }
    else if(last_phase == PHASE_A && new_phase == PHASE_D)
    {
        phasen_counter--;
        direction = 'b';
    }
    else if(last_phase == PHASE_D && new_phase == PHASE_C)
    {
        phasen_counter--;
        direction = 'b';
    }
    else if(last_phase == PHASE_C && new_phase == PHASE_B)
    {
        phasen_counter--;
        direction = 'b';
    }
    else
    {
        error = 1;
    }

    last_phase = new_phase;
}

int fsm_get_counter(void) /*gibt die Anzahl der Phasenwechsel aus*/
{
    return phasen_counter;
}
int fsm_has_error(void) /*gibt fehlerstatus*/
{
    return error;
}
char fsm_get_direction(void) /*gibt die aktuelle drehrichtung*/
{
    return direction;
}
void fsm_reset_error(void) /*setzt den fehler wieder auf kein feheler*/
{
    error = 0;
}
void fsm_reset_counter(void) /*setzt den zähler zurück und setzt drehrichtung auf stillstehnd*/
{
    phasen_counter = 0; direction = 'i';
}
void fsm_reset(void)
{
    phasen_counter = 0; direction = 'i'; last_phase = PHASE_B; error = 0;
}