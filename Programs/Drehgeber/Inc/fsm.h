#ifndef FSM_H
#define FSM_H

#include "gpio.h"


void fsm_update(Phase newphase);
int fsm_get_counter(void);
int fsm_has_error(void);
char fsm_get_direction(void);
void fsm_reset_error(void);
void fsm_reset_counter(void);
void fsm_reset(void);

#endif /* FSM_H */