#include "Vec3.h"
#include <cmath>

#include "Utils.h"

Vec3::Vec3(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

double Vec3::magnitude()
{
    return sqrt(x * x + y * y + z * z);
}

Vec3 Vec3::operator-(Vec3 input)
{
    return Vec3(x - input.x, y - input.y, z - input.z);
}

Vec3 Vec3::operator-()
{
    return Vec3(-x, -y, -z);
}

Vec3 Vec3::operator+(Vec3 input)
{
    return Vec3(x + input.x, y + input.y, z + input.z);
}

Vec3 Vec3::operator+(double input)
{
    return Vec3(x + input, y + input, z + input);
}

void Vec3::operator-=(Vec3 input)
{
    x -= input.x;
    y -= input.y;
    z -= input.z;
}

void Vec3::operator+=(Vec3 input)
{
    x += input.x;
    y += input.y;
    z += input.z;
}

Vec3 Vec3::operator*(double input)
{
    return Vec3(x * input, y * input, z * input);
}

void Vec3::operator=(Vec3 input)
{
    x = input.x;
    y = input.y;
    z = input.z;
}

bool Vec3::operator==(Vec3 input)
{
    return compare(x, input.x) && compare(y, input.y);
}

std::string Vec3::toString()
{
    return std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z);
}