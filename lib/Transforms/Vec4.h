#ifndef Vec4_H
#define Vec4_H

#include "Vec3.h"

class Vec4
{
public:
    double x;
    double y;
    double z;
    double w;

    Vec4(){};
    Vec4(Vec3 vec, double w);
    Vec4(double x, double y, double z, double w);

    operator Vec3() const;
};

#endif
