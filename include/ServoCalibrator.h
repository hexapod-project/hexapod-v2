#ifndef ServoCalibrator_H
#define ServoCalibrator_H

#include <Adafruit_PWMServoDriver.h>

class ServoCalibrator
{
private:
    const int PWM_FREQ = 50;
    const int MIN_PULSE = 500;
    const int MAX_PULSE = 2650;
    int pinNo = -1;

    Adafruit_PWMServoDriver *selectedDriver;

    Adafruit_PWMServoDriver *driverRight = new Adafruit_PWMServoDriver(0x40);
    Adafruit_PWMServoDriver *driverLeft = new Adafruit_PWMServoDriver(0x41);

    void selectSides();
    void selectPinNo();
    void setPWMPeriod();

public:
    void setup();
    void loop();
};

#endif