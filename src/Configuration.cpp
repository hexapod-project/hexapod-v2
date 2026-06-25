#include "Configuration.h"
#include "Vec3.h"

Adafruit_PWMServoDriver *servoDriverLeft = new Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver *servoDriverRight = new Adafruit_PWMServoDriver(0x41);

std::map<int, Servo *> SERVOS = {
    {1, new Servo(servoDriverLeft, 15, 750, 2250)},
    {2, new Servo(servoDriverLeft, 14, 750, 2250)},
    {3, new Servo(servoDriverLeft, 13, 750, 2250)},
    {4, new Servo(servoDriverLeft, 7, 750, 2250)},
    {5, new Servo(servoDriverLeft, 6, 750, 2250)},
    {6, new Servo(servoDriverLeft, 5, 750, 2250)},
    {7, new Servo(servoDriverLeft, 2, 750, 2250)},
    {8, new Servo(servoDriverLeft, 1, 750, 2250)},
    {9, new Servo(servoDriverLeft, 0, 750, 2250)},
    {10, new Servo(servoDriverRight, 0, 750, 2250)},
    {11, new Servo(servoDriverRight, 1, 750, 2250)},
    {12, new Servo(servoDriverRight, 2, 750, 2250)},
    {13, new Servo(servoDriverRight, 8, 750, 2250)},
    {14, new Servo(servoDriverRight, 9, 750, 2250)},
    {15, new Servo(servoDriverRight, 10, 750, 2250)},
    {16, new Servo(servoDriverRight, 13, 750, 2250)},
    {17, new Servo(servoDriverRight, 14, 750, 2250)},
    {18, new Servo(servoDriverRight, 15, 750, 2250)},
};

std::map<int, Leg *> LEGS = {
    {LegType::LEFT_FRONT, new Leg(120, SERVOS[Joint::LEFT_FRONT_COXA], SERVOS[Joint::LEFT_FRONT_FEMUR], SERVOS[Joint::LEFT_FRONT_TIBIA])},
    {LegType::LEFT_MID, new Leg(180, SERVOS[Joint::LEFT_MID_COXA], SERVOS[Joint::LEFT_MID_FEMUR], SERVOS[Joint::LEFT_MID_TIBIA])},
    {LegType::LEFT_BACK, new Leg(-120, SERVOS[Joint::LEFT_BACK_COXA], SERVOS[Joint::LEFT_BACK_FEMUR], SERVOS[Joint::LEFT_BACK_TIBIA])},
    {LegType::RIGHT_FRONT, new Leg(60, SERVOS[Joint::RIGHT_FRONT_COXA], SERVOS[Joint::RIGHT_FRONT_COXA], SERVOS[Joint::RIGHT_FRONT_COXA])},
    {LegType::RIGHT_MID, new Leg(0, SERVOS[Joint::RIGHT_MID_COXA], SERVOS[Joint::RIGHT_MID_FEMUR], SERVOS[Joint::RIGHT_MID_TIBIA])},
    {LegType::RIGHT_BACK, new Leg(-60, SERVOS[Joint::RIGHT_BACK_COXA], SERVOS[Joint::RIGHT_BACK_FEMUR], SERVOS[Joint::RIGHT_BACK_TIBIA])},
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