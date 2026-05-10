#ifndef DISPLAY_H
#define DISPLAY_H


#define STARTY 0
#define STARTX 0

void display_init(void);

void display_update(double winkel, double Geschwinigkeit);

void prepareLCDUpdate(double angle, double velocity);

void processLCDUpdate(void);

#endif