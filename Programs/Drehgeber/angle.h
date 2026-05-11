/**
 ******************************************************************************
 * @file    angle.h
 * @author  Timo Hinrichs, Emre Hakli
 * @brief   Funktionen zum Berechnen von werten für den Drehgeber
 ******************************************************************************
 */

#ifndef ANGLE_H
#define ANGLE_H

#define ANGLE_PER_PHASE 0.3
#define TICKS_PER_SEC 90e6

/** 
********************************************************************************
* @brief  Berechnet die Winkelgeschwindigkeit.
* @param int PhaseDiff (menge an phasenwechseln), double deltaTime
* @retval Winkelgeschwindigkeit in gegebenem Zeitraum.
*/
double getVelocity(int phaseDiff, double deltaTime);

/** 
********************************************************************************
* @brief  Berechnet den bisher gelaufenen Winkel anhand der Schrittanzahl
* @param steps Anzahl an Schritten
* @retval Winkel
*/
double calculateAngle(int steps);


#endif /* ANGLE_H */
// EOF