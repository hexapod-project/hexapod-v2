#pragma once

#include <stdint.h>
#include <string>

bool compare(double a, double b);
double toDegrees(double radians);
double toRadians(double degrees);
double toPositiveDeg(double deg);
double toPositiveRad(double rad);
double clampTo360Deg(double deg);
double clampTo360Rad(double rad);
uint8_t *shortsToByteArray(u_int16_t* shortArray, uint16_t arraySize);
std::string byteArrayToString(u_int8_t* byteArray, uint16_t arraySize);