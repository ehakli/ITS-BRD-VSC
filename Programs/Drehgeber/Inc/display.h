#ifndef DISPLAY_H
#define DISPLAY_H

void display_init(void);

void display_update(double winkel, double Geschwinigkeit);

void prepareLCDUpdate(double angle, double velocity);

void processLCDUpdate(void);

#endif