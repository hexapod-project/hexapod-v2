#ifndef Hexapod_H
#define Hexapod_H

#include "Leg.h"
#include <map>
#include "Mat4.h"

#define LEGS_COUNT 6

enum HexapodState {
    IDLE,
    WALK
};

class Hexapod
{
private:
    Mat4 matrix;
    Mat4 originalMatrix;
    Leg *legs[LEGS_COUNT];

    void resetMatrix();
    void rest();
    void stand();
    void updateLegs();

public:
    Hexapod();
    void init();
    void update();
    void walk(double walkDirection);
    void rotate(double angle);
    void rollAndPitch(double roll, double pitch);
};

#endif