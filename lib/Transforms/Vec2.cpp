#include "Vec2.h"
#include <cmath>
#include "Utils.h"

Vec2::Vec2(double pos)
{
    this->x = pos;
    this->y = pos;
}

Vec2::Vec2(double x, double y)
{
    this->x = x;
    this->y = y;
}

double Vec2::magnitude()
{
    return sqrt(x * x + y * y);
}

Vec2 Vec2::operator+=(Vec2 input)
{
    return Vec2(x + input.x, y + input.y);
}

Vec2 Vec2::operator/(double input)
{
    return Vec2(x / input, y / input);
}

Vec2 Vec2::operator/(Vec2 input)
{
    return Vec2(x / input.x, y / input.y);
}

Vec2 Vec2::operator-(Vec2 input)
{
    return Vec2(x - input.x, y - input.y);
}

bool Vec2::operator==(Vec2 input)
{
    return compare(x, input.x) && compare(y, input.y);
}

bool Vec2::operator!=(Vec2 input)
{
    return !compare(x, input.x) || !compare(y, input.y);
}

std::string Vec2::toString()
{
    return std::to_string(x) + ", " + std::to_string(y);
}
