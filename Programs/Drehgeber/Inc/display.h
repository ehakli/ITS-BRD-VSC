#ifndef DISPLAY_H
#define DISPLAY_H


#define ANGLEY 0
#define ANGLEX 0
#define VELOCITY_Y 1
#define VELOCITYX 0

void display_init(void);

void display_update(double winkel, double Geschwinigkeit);

void prepareVelocityBuffer(double velocity);
void prepareAngleBuffer(double Angle);

void processLCDUpdate(void);
void processLCDUpdate2(void);

#endif