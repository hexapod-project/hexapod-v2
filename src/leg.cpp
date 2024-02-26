#include "leg.h"
#include <cmath>

Leg::Leg(Point coxaPosition, double femurLength, double tibiaLength, double baseAngle, Servo *coxaServo, Servo *femurServo, Servo *tibiaServo)
{
    this->coxaPosition = coxaPosition;
    this->femurLength = femurLength;
    this->tibiaLength = tibiaLength;
    this->baseAngle = baseAngle;
    this->coxaServo = coxaServo;
    this->femurServo = femurServo;
    this->tibiaServo = tibiaServo;
}

double Leg::getCoxaAngle(Point globalPos)
{
    Point pos = globalPos - this->coxaPosition;

    double targetAngle = atan2(pos.getY(), pos.getX());

    return targetAngle - baseAngle;
}

double Leg::getFemurAngle(double targetDist)
{
    double a = this->femurLength;
    double b = targetDist;
    double c = this->tibiaLength;

    return acos((a * a + b * b - c * c) / 2 * a * b);
}

double Leg::getTibiaAngle(double targetDist)
{
    double a = this->femurLength;
    double b = targetDist;
    double c = this->tibiaLength;

    return acos((a * a + c * c - b * b) / 2 * a * c);
}

void Leg::update() {

}

void Leg::moveFeet(Point globalPos)
{
    double targetDist = this->coxaPosition.getDistance(globalPos);
    double coxaAngle = getCoxaAngle(globalPos);
    double femurAngle = getFemurAngle(targetDist);
    double tibiaAngle = getTibiaAngle(targetDist);

    coxaServo->setAngle(coxaAngle);
    femurServo->setAngle(femurAngle);
    tibiaServo->setAngle(tibiaAngle);
}