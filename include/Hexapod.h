#ifndef Hexapod_H
#define Hexapod_H

#include "Leg.h"
#include <map>
#include "Mat4.h"
#include "GaitsManager.h"

#define LEGS_COUNT 6

enum HexapodState
{
    IDLE,
    WALK
};

class Hexapod
{
private:
    Mat4 matrix;
    Mat4 originalMatrix;
    Leg *legs[LEGS_COUNT];

    GaitsManager gaitsManager;

    void resetMatrix();

public:
    void init();
    void startWalk(double walkDirection);
    void walk(WalkTranslations stepValues);
    void startRotate(RotateDirection rotateDirection);
    void rotate(Rotations rotateTranslations);
    void rollAndPitch(double roll, double pitch);
    void stop();
    void rest();
    void stand();
};

#endif