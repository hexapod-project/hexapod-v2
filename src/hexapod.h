#ifndef Hexapod_H
#define Hexapod_H

#include "leg.h"
#include <map>

#define LEGS_COUNT 6

enum LEG
{
    RIGHT_FRONT,
    RIGHT_MID,
    RIGHT_BACK,
    LEFT_FRONT,
    LEFT_MID,
    LEFT_BACK
};

class Hexapod
{
private:
    double roll;
    double pitch;
    Leg *legs[];

public:
    Hexapod();
    void update();
    void walk(double walkDirection);
    void rotate(double angle);
    void rollAndPitch(double roll, double pitch);
};

#endif