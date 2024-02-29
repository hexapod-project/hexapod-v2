#ifndef Vec3_H
#define Vec3_H

#include <string>

class Vec3
{
public:
    double x = 0;
    double y = 0;
    double z = 0;

    Vec3() {};
    Vec3(double x, double y, double z);
    double magnitude();    
    Vec3 operator + (Vec3 input);        
    Vec3 operator + (double input);
    Vec3 operator - (Vec3 input);
    Vec3 operator-();
    Vec3 operator * (double input);
    void operator -= (Vec3 input);
    void operator += (Vec3 input);
    void operator = (Vec3 input);
    bool operator == (Vec3 input);
    std::string toString();
};

#endif