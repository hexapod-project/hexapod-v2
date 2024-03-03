#ifndef Configuration_H
#define Configuration_H

#include <map>
#include "Servo.h"
#include "Leg.h"
#include "Vec3.h"
#include <Adafruit_PWMServoDriver.h>

// 0 = Hexapod, 1 = Servo Calibration, 2 = Servo Tests
#define MODE 0
#define DEBUG_MODE_LEGS false
#define SERIAL_CONTROL_MODE false

// Servo Constants
#define SERVO_ANGLES_MIN -75
#define SERVO_ANGLES_MAX 75
#define PWM_FREQ 50

extern Adafruit_PWMServoDriver *servoDriverRight;
extern Adafruit_PWMServoDriver *servoDriverLeft;

extern std::map<int, Servo *> SERVOS;

// Leg Constants
// Lengths in mm
#define COXA_DISTANCE_FROM_CENTER 90
#define FEMUR_TO_COXA_DISTANCE 40
#define FEMUR_LENGTH 70
#define TIBIA_LENGTH 90

extern std::map<int, Leg *> LEGS;

//Body Positions
#define BODY_OFFSET_Z 10

// Feet Properties
#define REST_HEIGHT 0
#define STAND_HEIGHT 40
#define FEET_DISTANCE_FROM_CENTER_REST 180
#define FEET_DISTANCE_FROM_CENTER_STANDING 180

extern std::map<int, Vec3 *> FEET_POSITIONS_STANDING;
extern std::map<int, Vec3 *> FEET_POSITIONS_REST;

// Step Properties
#define STEP_FRAMERATE 24 //How often to update the gaits
#define STEP_DISTANCE 50
#define STEP_HEIGHT 40
#define STEP_DURATION 0.65//in seconds

// Roll Pitch Properties
#define ROLL_ANGLE 20
#define PITCH_ANGLE 20

// Rotate Properties
#define ROTATE_ANGLE_PER_STEP 10

#endif