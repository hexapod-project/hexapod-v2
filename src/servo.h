#ifndef Servo_H
#define Servo_H

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
    double getPulse(double angle);

public:
    Servo(Adafruit_PWMServoDriver *servoDriver, int pinNo, int minPulse, int maxPulse);
    void setAngle(double angle);
};

#endif