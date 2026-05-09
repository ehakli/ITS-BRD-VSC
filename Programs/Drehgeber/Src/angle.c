#include "angle.h"


double calculateAngle(int steps)
{
    return (double) (steps * ANGLE_PER_PHASE);
}


double getVelocity(int phaseDiff, int deltaTime)
{
    double deltaTime = deltaTime / 90e6

    (phaseDiff * 0,3) / deltaTime;
}