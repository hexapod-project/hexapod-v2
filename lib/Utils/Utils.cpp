#include "Utils.h"
#include <cmath>
#include <Arduino.h>

bool compare(double a, double b)
{
    return fabs(a - b) < __DBL_EPSILON__;
}

double toDegrees(double radians)
{
    return radians * 180 / M_PI;
}

double toRadians(double degrees)
{
    return degrees * M_PI / 180;
}

double toPositiveDeg(double deg)
{
    if(deg < 0)
        deg = 360 + deg;

    return deg;
}

double toPositiveRad(double rad)
{
    if(rad < 0)
        rad = M_TWOPI + rad;

    return rad;
}

double clampTo360Deg(double deg)
{
    if(fabs(deg) > 360)
        deg = copysign(fmod(fabs(deg), 360), deg);

    return deg;
}

double clampTo360Rad(double rad)
{
    if(fabs(rad) > 2 * M_PI)
        rad = copysign(fmod(fabs(rad), 2 * M_PI), rad);

    return rad;
}
