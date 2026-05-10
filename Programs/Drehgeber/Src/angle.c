#include "angle.h"


double calculateAngle(int steps)
{
    return (double) (steps * ANGLE_PER_PHASE);
}


double getVelocity(int phaseDiff, double deltaTime)
{
    if(deltaTime <= 0) return 0.0;

    
    return (phaseDiff * 0.3) / deltaTime;
}