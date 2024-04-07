#include "Calibrator.h"
#include "Configuration.h"
#include "Constants.h"
#include "Utils.h"

const char *CALIBRATION_NAMESPACE = "calibration";

Calibrator::Calibrator(Hexapod *hexapod)
{
    this->hexapod = hexapod;
}

void Calibrator::init()
{
    preferences.begin(CALIBRATION_NAMESPACE, false);
    preferences.end();

    initializeServoCalibrations();
}

void Calibrator::initializeServoCalibrations()
{
    preferences.begin(CALIBRATION_NAMESPACE, true);

    for (int i = 0; i < SERVO_COUNT; i++)
    {
        uint16_t averagePulse = preferences.getUInt(std::to_string(i).c_str());

        if (averagePulse > 0)
        {
            SERVOS[i + 1]->calibrate(averagePulse);
        }
    }

    preferences.end();
}

void Calibrator::setPWMPulse(int servoIndex, uint16_t averagePulse)
{
    if (hexapod->getMode() != HexapodMode::CALIBRATE)
    {
        return;
    }

    SERVOS[servoIndex + 1]->calibrate(averagePulse);
    SERVOS[servoIndex + 1]->setAngle(0);

    preferences.begin(CALIBRATION_NAMESPACE, false);
    preferences.putUShort(std::to_string(servoIndex).c_str(), averagePulse);
    preferences.end();
}

void Calibrator::testServoAngle(int servoIndex, short degrees)
{
    if (hexapod->getMode() != HexapodMode::CALIBRATE)
    {
        return;
    }

    SERVOS[servoIndex + 1]->setAngle(degrees);
}

uint8_t *Calibrator::getCalibrationSettings()
{
    preferences.begin(CALIBRATION_NAMESPACE, true);

    uint16_t pulseArray[SERVO_COUNT];

    for (int i = 0; i < SERVO_COUNT; i++)
    {
        uint16_t pulse = preferences.getUShort(std::to_string(i).c_str());

        if (pulse == 0)
        {
            pulse = SERVOS[i + 1]->getAveragePulse();
        }

        pulseArray[i] = pulse;
    }

    preferences.end();

    return shortsToByteArray(pulseArray, SERVO_COUNT);
}