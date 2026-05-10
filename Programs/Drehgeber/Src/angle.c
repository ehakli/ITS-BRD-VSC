#include "angle.h"


double calculateAngle(int steps)
{
    return (double) (steps * ANGLE_PER_PHASE);
}


double getVelocity(int phaseDiff, int deltaTime)
{
    deltaTime /= 90e6;

    return (phaseDiff * 0,3) / deltaTime;
}