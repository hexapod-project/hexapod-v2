#pragma once

#include <Adafruit_PWMServoDriver.h>

struct ServoPulse
{
    int min;
    int max;

    ServoPulse(int min, int max)
    {
        this->min = min;
        this->max = max;
    }
};

class Servo
{
private:
    Adafruit_PWMServoDriver *servoDriver;
    int pinNo;
    int minPulse;
    int maxPulse;
    double getPulse(double radians);

public:
    Servo(Adafruit_PWMServoDriver *servoDriver, int pinNo, int minPulse, int maxPulse);
    int getAveragePulse();
    void setAngle(double radians);
    void calibrate(int averagePulse);
};