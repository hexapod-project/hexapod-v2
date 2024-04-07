#pragma once

#include "Leg.h"
#include <map>
#include "Mat4.h"
#include "GaitsManager.h"
#include "Enums.h"

#define LEGS_COUNT 6

class Hexapod
{
private:
    HexapodMode mode = HexapodMode::CONTROLLER;

    Mat4 matrix;
    Mat4 originalMatrix;
    Leg *legs[LEGS_COUNT];

    GaitsManager gaitsManager;

    void resetMatrix();
    void initNormalMode();
    void initCalibrateMode();

public:
    void init();
    void startWalk(double walkDirection);
    //This is called by GaitManager's walk cycle
    void walk(WalkTranslations stepValues);
    //This is called by GaitManager's rotate cycle
    void startRotate(RotateDirection rotateDirection);
    void rotate(Rotations rotateTranslations);
    void rollAndPitch(double roll, double pitch);
    void stop();
    void rest();
    void stand();
    HexapodMode getMode();
    void switchMode(HexapodMode mode);
};