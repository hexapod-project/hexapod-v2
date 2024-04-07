#include <algorithm>

#include "Servo.h"
#include "Configuration.h"
#include "Constants.h"

Servo::Servo(Adafruit_PWMServoDriver *servoDriver, int pinNo, int minPulse, int maxPulse)
{
    this->servoDriver = servoDriver;
    this->pinNo = pinNo;
    this->minPulse = minPulse;
    this->maxPulse = maxPulse;
}

double Servo::getPulse(double angle)
{
    angle = std::clamp(angle, (double)SERVO_ANGLES_MIN, (double)SERVO_ANGLES_MAX);
    return map(angle, SERVO_ANGLES_MIN, SERVO_ANGLES_MAX, this->minPulse, this->maxPulse);
}

void Servo::setAngle(double angle)
{
    servoDriver->writeMicroseconds(pinNo, getPulse(angle));
}

int Servo::getAveragePulse()
{
    return round((this->minPulse + this->maxPulse) / 2.0);
}

void Servo::calibrate(int averagePulse)
{
    this->minPulse = averagePulse - SERVO_PULSE_INTERVAL;
    this->maxPulse = averagePulse + SERVO_PULSE_INTERVAL;
}