#ifndef ServoTester_H
#define ServoTester_H

#include <Adafruit_PWMServoDriver.h>
#include "Servo.h"

class ServoTester
{
private:
    int angle = 0;
    Servo *selectedServo;
    
    void selectServoNo();
    void setAngle();

public:
    void setup();
    void loop();
};

#endif