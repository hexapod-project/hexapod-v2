#ifndef Leg_H
#define Leg_H

#include <vector>
#include "Servo.h"
#include "Vec3.h"
#include "Mat4.h"

enum LegType
{
    LEFT_FRONT,
    LEFT_MID,
    LEFT_BACK,
    RIGHT_FRONT,
    RIGHT_MID,
    RIGHT_BACK,
};

class Leg
{
private:
    Mat4 matrix;
    Vec3 currentFeetPosition;
    Mat4 *root = new Mat4();
    double baseAngle;
    Servo *coxaServo;
    Servo *femurServo;
    Servo *tibiaServo;
    double getCoxaAngle(Vec3 feetPosition);
    double getFemurAngle(Vec3 feetPosition);
    double getTibiaAngle(Vec3 feetPosition);
    double checkAngleOrientation(double angle);

public:
    Leg(double angle, Servo *coxaServo, Servo *femurServo, Servo *tibiaServo);
    void update();
    void setRoot(Mat4 *root);
    void setFeetPosition(Vec3 feetPosition);    
    double getBaseAngle();
    double getBaseAngleInRadians();
};

#endif