/**
 ******************************************************************************
 * @file    display.h
 * @author  Timo Hinrichs, Emre Hakli
 * @brief   Statemaschine für den Drehgeber
 ******************************************************************************
 */



#ifndef DISPLAY_H
#define DISPLAY_H


#define ANGLEY 0
#define ANGLEX 0
#define VELOCITY_Y 1
#define VELOCITYX 0

/** 
********************************************************************************
* @brief  Initialisiert das Display mit dem Starttext
* @param void
* @retval void
*/

void display_init(void);

/** 
********************************************************************************
* @brief  Formatiert den Winkelwert zu einem String und setzt den Index vom Anglebuffer auf 0
* @param Angle
* @retval void
*/

void prepareAngleBuffer(double Angle);

/** 
********************************************************************************
* @brief  Formatiert die Geschwindigkeit zu einem String und setzt den Index vom Velocitybuffer auf 0
* @param velocity
* @retval void
*/

void prepareVelocityBuffer(double velocity);

/** 
********************************************************************************
* @brief  Schreibt pro Aufruf genau ein Zeichen aufs Display, zuerst Winkel dann Geschwindigkeit
* @param void
* @retval void
*/

void processLCDUpdate(void);

/** 
********************************************************************************
* @brief  Schreibt pro Aufruf genau ein Zeichen aufs Display, zuerst Winkel dann Geschwindigkeit
* @param void
* @retval void
*/
void processLCDUpdate2(void);

#endif