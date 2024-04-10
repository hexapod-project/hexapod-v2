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
    bool _isRest = false;

    Mat4 matrix;
    Mat4 originalMatrix;
    Mat4 standMatrix;
    Mat4 walkMatrix;
    Leg *legs[LEGS_COUNT];

    GaitsManager gaitsManager;

    void resetMatrix();
    void initNormalMode();
    void initCalibrateMode();

public:
    void init();
    void startWalk(double walkDirection);
    // This is called by GaitManager's walk cycle
    void walk(WalkPositions stepValues);
    // This is called by GaitManager's rotate cycle
    void startRotate(RotateDirection rotateDirection);
    void rotate(Rotations rotateTranslations);
    void rollAndPitch(double angle);
    void stop();
    void rest();
    void stand();
    HexapodMode getMode();
    bool isRest();
    void switchMode(HexapodMode mode);
};