#pragma once

#include "Hexapod.h"
#include <Preferences.h>

class Calibrator
{
private:
    Hexapod *hexapod = nullptr;
    Preferences preferences;


public:
    Calibrator(Hexapod *hexapod);
    void init();
    void initializeServoCalibrations();
    void setPWMPulse(int servoIndex, uint16_t averagePulse);
    void testServoAngle(int servoIndex, short degrees);
    uint8_t* getCalibrationSettings();
};