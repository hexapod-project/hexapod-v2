#pragma once

#include "Hexapod.h"
#include <Preferences.h>

class Calibrator
{
private:
    static Calibrator *instance;
    Hexapod *hexapod = nullptr;
    Preferences preferences;

public:
    Calibrator(Hexapod *hexapod);
    static Calibrator* getInstance();
    void init();
    void initializeServoCalibrations();
    void setPWMPulse(int servoIndex, uint16_t averagePulse);
    void testServoAngle(int servoIndex, short degrees);
    uint8_t *getCalibrationSettings();
    uint16_t getPWMPulse(int servoIndex);
    void resetToDefault();
};