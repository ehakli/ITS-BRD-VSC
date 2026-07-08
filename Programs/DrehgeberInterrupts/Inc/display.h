/**
 ******************************************************************************
 * @file    display.h
 * @author  Timo Hinrichs, Emre Hakli
 * @brief   Funktionen zur Ansteuerung des Displays bei dem Drehgeber.
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
* @brief  Speichert den Winkel als charArray (um somit auch die Ausgabe als Kommazahl zu ermoeglichen.)
* @param Angle 
* @retval void
*/
void prepareAngleBuffer(double Angle);

/** 
********************************************************************************
* @brief  Speichert die Geschwindigkeit als charArray
* @param velocity
* @retval void
*/
void prepareVelocityBuffer(double velocity);

/** 
********************************************************************************
* @brief  Schreibt jeweils eine Ziffer beider BufferArrays auf den LCD Screen an ihre jeweilige Stellen.
* @param void
* @retval void
*/
void processLCDUpdate(void);


#endif