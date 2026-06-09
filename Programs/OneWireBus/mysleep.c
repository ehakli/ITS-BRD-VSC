#include "timer.h"
#include <stdint.h>

void sleep(uint32_t time_us)
{
    uint32_t startTime = getTimeStamp();

    uint32_t ticksWait = time_us * TICKS_PER_US;

    while((getTimeStamp() - startTime) < ticksWait)
    {
        //wait
    }
}