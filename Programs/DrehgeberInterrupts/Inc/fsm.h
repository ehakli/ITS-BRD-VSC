/**
 ******************************************************************************
 * @file    fsm.h
 * @author  Timo Hinrichs, Emre Hakli
 * @brief   Statemaschine für den Drehgeber
 ******************************************************************************
 */


#ifndef FSM_H
#define FSM_H

#include "gpio.h"

/** 
********************************************************************************
* @brief  Aktuallisiert den State der Maschine
* @param newphase
* @retval void
*/
void fsm_update(Phase newphase);
/** 
********************************************************************************
* @brief  Gibt den aktuellen Zählerstand des Phasenzählers
* @param void
* @retval Der Zählerstand
*/

int fsm_get_counter(void);
/** 
********************************************************************************
* @brief  Gibt die aktuelle richtung, in die sich der Drehgeber dreht
* @param void
* @retval die Richtung
*/

char fsm_get_direction(void);
/** 
********************************************************************************
* @brief  Setzt den aktuellen Zählerstand des Phasenzählers auf 0
* @param void
* @retval void
*/
void fsm_reset_counter(void);

/** 
********************************************************************************
* @brief  Setzt die komplette FSM Auf Anfang zurück
* @retval void
*/
void fsm_reset(void);

#endif /* FSM_H */