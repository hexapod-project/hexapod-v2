#include "servo.h"

Servo::Servo(Adafruit_PWMServoDriver *servoDriver, int pinNo, int minPulse, int maxPulse)
{
    this->servoDriver = servoDriver;
    this->pinNo = pinNo;
    this->minPulse = minPulse;
    this->maxPulse = maxPulse;
}

double Servo::getPulse(double angle)
{
    return map(angle, this->minPulse, this->maxPulse, -45.0, 45.0);
}

void Servo::setAngle(double angle)
{
    servoDriver->writeMicroseconds(this->pinNo, getPulse(angle));
}