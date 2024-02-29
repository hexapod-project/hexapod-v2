#ifndef Vec2_H
#define Vec2_H

#include <string>

class Vec2
{
public:
    double x;
    double y;

    Vec2(){};
    Vec2(double pos);
    Vec2(double x, double y);
    double magnitude();

    Vec2 operator+=(Vec2 input);
    Vec2 operator/(double input);
    Vec2 operator/(Vec2 input);
    Vec2 operator-(Vec2 input);
    bool operator==(Vec2 input);
    bool operator!=(Vec2 input);

    std::string toString();
};

#endif