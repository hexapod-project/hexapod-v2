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

double getDeltaTime() {
    double cpuFreq = getCpuFrequencyMhz();

    return 1/cpuFreq;
}