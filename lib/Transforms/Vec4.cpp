#include "Vec4.h"

Vec4::Vec4(double x, double y, double z, double w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

Vec4::Vec4(Vec3 vec, double w)
{
    x = vec.x;
    y = vec.y;
    z = vec.z;
    this->w = w;
}

Vec4::operator Vec3() const
{
    return Vec3(this->x, this->y, this->z);
}