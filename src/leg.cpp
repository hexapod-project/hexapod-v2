#include "Leg.h"
#include <cmath>
#include "Configuration.h"
#include "Utils.h"
#include "Vec2.h"

Leg::Leg(double baseAngle, Servo *coxaServo, Servo *femurServo, Servo *tibiaServo)
{
    this->baseAngle = baseAngle;

    Vec3 coxaPosition = Vec3(cos(getBaseAngleInRadians()) * COXA_DISTANCE_FROM_CENTER, sin(getBaseAngleInRadians()) * COXA_DISTANCE_FROM_CENTER, 0);
    this->matrix = this->matrix.translate(coxaPosition);

    this->coxaServo = coxaServo;
    this->femurServo = femurServo;
    this->tibiaServo = tibiaServo;
}

void Leg::setRoot(Mat4 *root)
{
    this->root = root;
}

double Leg::getBaseAngle()
{
    return baseAngle;
}

double Leg::getBaseAngleInRadians()
{
    return toRadians(baseAngle);
}

double Leg::getCoxaAngle(Vec3 feetPosition)
{
    double radians = atan2(feetPosition.y, fabs(feetPosition.x));

    double angle = toDegrees(radians);

    if (fabs(baseAngle) > 90)
    {
        angle -= (copysignf(180, baseAngle) - baseAngle);
    } else {
        angle -= baseAngle;
    }

    return -angle;
}

double Leg::getFemurAngle(Vec3 feetPosition)
{
    double angleOffset = atan2(feetPosition.z, fabs(Vec2(feetPosition.x, feetPosition.y).magnitude()));

    double a = FEMUR_LENGTH;
    double b = TIBIA_LENGTH;
    double c = feetPosition.magnitude();

    double radians = -acos((a * a + c * c - b * b) / (2 * a * c));
    radians -= angleOffset;

    return toDegrees(radians);
}

double Leg::getTibiaAngle(Vec3 feetPosition)
{
    double a = FEMUR_LENGTH;
    double b = TIBIA_LENGTH;
    double c = feetPosition.magnitude();

    double radians = -(M_PI_2 - acos((a * a + b * b - c * c) / (2 * a * b)));

    return toDegrees(radians);
}

double Leg::checkAngleOrientation(double angle)
{
    if (fabs(baseAngle) > 90)
    {
        angle = -angle;
    }

    return angle;
}

void Leg::setFeetPosition(Vec3 globalFeetPosition)
{
    Mat4 inverseMatrix = root->multiply(matrix).inverse();
    Vec3 localFeetPosition = inverseMatrix.multiply(Vec4(globalFeetPosition, 1));

    double coxaAngle = getCoxaAngle(localFeetPosition);

    double globalCoxaRadians = toRadians(baseAngle + coxaAngle);
    Vec3 femurOffset = Vec3(cos(globalCoxaRadians) * FEMUR_TO_COXA_DISTANCE, sin(globalCoxaRadians) * FEMUR_TO_COXA_DISTANCE, 0);
    Vec3 offsetFeetPosition = localFeetPosition - femurOffset;
    double femurAngle = getFemurAngle(offsetFeetPosition);

    double tibiaAngle = getTibiaAngle(offsetFeetPosition);

    coxaAngle = checkAngleOrientation(coxaAngle);
    femurAngle = checkAngleOrientation(femurAngle);
    tibiaAngle = checkAngleOrientation(tibiaAngle);

    coxaServo->setAngle(coxaAngle);
    femurServo->setAngle(femurAngle);
    tibiaServo->setAngle(tibiaAngle);

    currentFeetPosition = globalFeetPosition;

    if (DEBUG_MODE)
    {
        Serial.print("BaseAngle:");
        Serial.println(baseAngle);
        Serial.print("feetPosition:");
        Serial.println(localFeetPosition.toString().c_str());
        Serial.print("offsetFeetPosition:");
        Serial.println(offsetFeetPosition.toString().c_str());
        Serial.print("coxaAngle:");
        Serial.print(coxaAngle);
        Serial.print(", femurAngle:");
        Serial.print(femurAngle);
        Serial.print(", tibiaAngle:");
        Serial.println(tibiaAngle);
        Serial.println("---------------------------");
    }
}

void Leg::update()
{
    setFeetPosition(currentFeetPosition);
}