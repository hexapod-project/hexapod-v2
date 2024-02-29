#include "Configuration.h"
#include "Vec3.h"

Adafruit_PWMServoDriver *servoDriverRight = new Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver *servoDriverLeft = new Adafruit_PWMServoDriver(0x41);

std::map<int, Servo *> SERVOS = {
    {1, new Servo(servoDriverLeft, 0, 850, 2350)},
    {2, new Servo(servoDriverLeft, 1, 950, 2450)},
    {3, new Servo(servoDriverLeft, 2, 750, 2250)},
    {4, new Servo(servoDriverLeft, 9, 925, 2425)},
    {5, new Servo(servoDriverLeft, 10, 750, 2250)},
    {6, new Servo(servoDriverLeft, 11, 800, 2300)},
    {7, new Servo(servoDriverLeft, 13, 750, 2250)},
    {8, new Servo(servoDriverLeft, 14, 750, 2250)},
    {9, new Servo(servoDriverLeft, 15, 700, 2200)},
    {10, new Servo(servoDriverRight, 15, 850, 2350)},
    {11, new Servo(servoDriverRight, 14, 800, 2300)},
    {12, new Servo(servoDriverRight, 13, 750, 2250)},
    {13, new Servo(servoDriverRight, 6, 825, 2325)},
    {14, new Servo(servoDriverRight, 5, 750, 2250)},
    {15, new Servo(servoDriverRight, 4, 750, 2250)},
    {16, new Servo(servoDriverRight, 2, 850, 2350)},
    {17, new Servo(servoDriverRight, 1, 750, 2250)},
    {18, new Servo(servoDriverRight, 0, 700, 2200)},
};

std::map<int, Leg *> LEGS = {
    {LegType::LEFT_FRONT, new Leg(120, SERVOS[1], SERVOS[2], SERVOS[3])},
    {LegType::LEFT_MID, new Leg(180, SERVOS[4], SERVOS[5], SERVOS[6])},
    {LegType::LEFT_BACK, new Leg(-120, SERVOS[7], SERVOS[8], SERVOS[9])},
    {LegType::RIGHT_FRONT, new Leg(60, SERVOS[10], SERVOS[11], SERVOS[12])},
    {LegType::RIGHT_MID, new Leg(0, SERVOS[13], SERVOS[14], SERVOS[15])},
    {LegType::RIGHT_BACK, new Leg(-60, SERVOS[16], SERVOS[17], SERVOS[18])},
};

std::map<int, Vec3 *> FEET_POSITIONS_REST = {
    {LegType::LEFT_FRONT, new Vec3(cos(LEGS[LegType::LEFT_FRONT]->getBaseAngleInRadians()) * FEET_DISTANCE_FROM_CENTER_REST, sin(LEGS[LegType::LEFT_FRONT]->getBaseAngleInRadians()) * FEET_DISTANCE_FROM_CENTER_REST, 0)},
    {LegType::LEFT_MID, new Vec3(cos(LEGS[LegType::LEFT_MID]->getBaseAngleInRadians()) * FEET_DISTANCE_FROM_CENTER_REST, sin(LEGS[LegType::LEFT_MID]->getBaseAngleInRadians()) * FEET_DISTANCE_FROM_CENTER_REST, 0)},
    {LegType::LEFT_BACK, new Vec3(cos(LEGS[LegType::LEFT_BACK]->getBaseAngleInRadians()) * FEET_DISTANCE_FROM_CENTER_REST, sin(LEGS[LegType::LEFT_BACK]->getBaseAngleInRadians()) * FEET_DISTANCE_FROM_CENTER_REST, 0)},
    {LegType::RIGHT_FRONT, new Vec3(cos(LEGS[LegType::RIGHT_FRONT]->getBaseAngleInRadians()) * FEET_DISTANCE_FROM_CENTER_REST, sin(LEGS[LegType::RIGHT_FRONT]->getBaseAngleInRadians()) * FEET_DISTANCE_FROM_CENTER_REST, 0)},
    {LegType::RIGHT_MID, new Vec3(cos(LEGS[LegType::RIGHT_MID]->getBaseAngleInRadians()) * FEET_DISTANCE_FROM_CENTER_REST, sin(LEGS[LegType::RIGHT_MID]->getBaseAngleInRadians()) * FEET_DISTANCE_FROM_CENTER_REST, 0)},
    {LegType::RIGHT_BACK, new Vec3(cos(LEGS[LegType::RIGHT_BACK]->getBaseAngleInRadians()) * FEET_DISTANCE_FROM_CENTER_REST, sin(LEGS[LegType::RIGHT_BACK]->getBaseAngleInRadians()) * FEET_DISTANCE_FROM_CENTER_REST, 0)},
};

std::map<int, Vec3 *> FEET_POSITIONS_STANDING = {
    {LegType::LEFT_FRONT, new Vec3(cos(LEGS[LegType::LEFT_FRONT]->getBaseAngleInRadians()) * FEET_DISTANCE_FROM_CENTER_STANDING, sin(LEGS[LegType::LEFT_FRONT]->getBaseAngleInRadians()) * FEET_DISTANCE_FROM_CENTER_STANDING, 0)},
    {LegType::LEFT_MID, new Vec3(cos(LEGS[LegType::LEFT_MID]->getBaseAngleInRadians()) * FEET_DISTANCE_FROM_CENTER_STANDING, sin(LEGS[LegType::LEFT_MID]->getBaseAngleInRadians()) * FEET_DISTANCE_FROM_CENTER_STANDING, 0)},
    {LegType::LEFT_BACK, new Vec3(cos(LEGS[LegType::LEFT_BACK]->getBaseAngleInRadians()) * FEET_DISTANCE_FROM_CENTER_STANDING, sin(LEGS[LegType::LEFT_BACK]->getBaseAngleInRadians()) * FEET_DISTANCE_FROM_CENTER_STANDING, 0)},
    {LegType::RIGHT_FRONT, new Vec3(cos(LEGS[LegType::RIGHT_FRONT]->getBaseAngleInRadians()) * FEET_DISTANCE_FROM_CENTER_STANDING, sin(LEGS[LegType::RIGHT_FRONT]->getBaseAngleInRadians()) * FEET_DISTANCE_FROM_CENTER_STANDING, 0)},
    {LegType::RIGHT_MID, new Vec3(cos(LEGS[LegType::RIGHT_MID]->getBaseAngleInRadians()) * FEET_DISTANCE_FROM_CENTER_STANDING, sin(LEGS[LegType::RIGHT_MID]->getBaseAngleInRadians()) * FEET_DISTANCE_FROM_CENTER_STANDING, 0)},
    {LegType::RIGHT_BACK, new Vec3(cos(LEGS[LegType::RIGHT_BACK]->getBaseAngleInRadians()) * FEET_DISTANCE_FROM_CENTER_STANDING, sin(LEGS[LegType::RIGHT_BACK]->getBaseAngleInRadians()) * FEET_DISTANCE_FROM_CENTER_STANDING, 0)},
};