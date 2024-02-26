#ifndef Leg_H
#define Leg_H

#include <vector>
#include "servo.h"
#include "../lib/point.h"

class Leg
{
private:
    Point coxaPosition;
    double femurLength;
    double tibiaLength;
    double baseAngle;
    Servo *coxaServo;
    Servo *femurServo;
    Servo *tibiaServo;
    double getCoxaAngle(Point globalPos);
    double getFemurAngle(double targetDist);
    double getTibiaAngle(double targetDist);

    Point currFeetPosition;
    Point targetFeetPosition;

public:
    Leg(Point coxaPosition, double femurLength, double tibiaLength, double angle, Servo *coxaServo, Servo *femurServo, Servo *tibiaServo);
    void update();
    void moveFeet(Point globalPos);
};

#endif