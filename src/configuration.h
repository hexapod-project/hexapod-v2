#include <map>
#include "servo.h"
#include "leg.h"
#include "../lib/point.h"
#include <Adafruit_PWMServoDriver.h>

// Build Configurations
Adafruit_PWMServoDriver *servoDriver40 = new Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver *servoDriver41 = new Adafruit_PWMServoDriver(0x41);

std::map<int, Servo *> SERVOS = {
    {1, new Servo(servoDriver40, 0, 968, 1956)},
    {2, new Servo(servoDriver40, 1, 1039, 2025)},
    {3, new Servo(servoDriver40, 2, 1049, 1994)},
    {4, new Servo(servoDriver40, 3, 965, 1948)},
    {5, new Servo(servoDriver40, 4, 1025, 2022)},
    {6, new Servo(servoDriver40, 5, 1045, 1990)},
    {7, new Servo(servoDriver40, 6, 935, 1865)},
    {8, new Servo(servoDriver40, 7, 1045, 2035)},
    {9, new Servo(servoDriver40, 8, 1020, 1975)},
    {10, new Servo(servoDriver41, 0, 965, 1920)},
    {11, new Servo(servoDriver41, 1, 1035, 2015)},
    {12, new Servo(servoDriver41, 2, 965, 1925)},
    {13, new Servo(servoDriver41, 3, 965, 1960)},
    {14, new Servo(servoDriver41, 4, 1065, 2055)},
    {15, new Servo(servoDriver41, 5, 1080, 2010)},
    {16, new Servo(servoDriver41, 6, 995, 2000)},
    {17, new Servo(servoDriver41, 7, 1065, 2050)},
    {18, new Servo(servoDriver41, 8, 1140, 2085)}};

std::map<int, Leg *> LEGS = {
    {1, new Leg(Point(0, 0), 0, 0, 0, SERVOS[0], SERVOS[1], SERVOS[2])},
    {2, new Leg(Point(0, 0), 0, 0, 0, SERVOS[4], SERVOS[5], SERVOS[6])},
    {3, new Leg(Point(0, 0), 0, 0, 0, SERVOS[7], SERVOS[8], SERVOS[9])},
    {4, new Leg(Point(0, 0), 0, 0, 0, SERVOS[10], SERVOS[11], SERVOS[12])},
    {5, new Leg(Point(0, 0), 0, 0, 0, SERVOS[13], SERVOS[14], SERVOS[15])},
    {6, new Leg(Point(0, 0), 0, 0, 0, SERVOS[16], SERVOS[17], SERVOS[18])},
};

// Step Properties
#define STEP_DISTANCE 10
#define STEP_HEIGHT 10
#define STEP_DURATION 10
#define STEP_INTERVAL 0

// Roll Pitch Properties
#define ROLL_ANGLE 10
#define PITCH_ANGLE 10

// Rotate Properties
#define ROTATE_STEPANGLE 5