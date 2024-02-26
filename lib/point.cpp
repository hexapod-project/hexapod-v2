#include "point.h"
#include <cmath>

Point::Point()
{
    Point(0, 0, 0);
}

Point::Point(double x)
{
    Point(x, 0, 0);
}

Point::Point(double x, double y)
{
    Point(x, y, 0);
}

Point::Point(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

double Point::getX()
{
    return this->x;
}

double Point::getY()
{
    return this->y;
}

double Point::getZ()
{
    return this->z;
}

double Point::getDistance(Point const &b)
{
    double xDistSqr =   pow(b.x - this->x, 2);
    double yDistSqr =   pow(b.y - this->y, 2);
    double zDistSqr =   pow(b.z - this->z, 2);

    return sqrt(xDistSqr + yDistSqr + zDistSqr);
}

Point Point::operator-(Point const &b)
{
    Point point;

    point.x = this->x - b.x;
    point.y = this->y - b.y;
    point.z = this->z - b.z;

    return point;
}

Point Point::operator+(Point const &b)
{
    Point point;

    point.x = this->x + b.x;
    point.y = this->y + b.y;
    point.z = this->z + b.z;

    return point;
}

Point Point::operator*(Point const &b)
{
    Point point;

    point.x = this->x * b.x;
    point.y = this->y * b.y;
    point.z = this->z * b.z;

    return point;
}

Point Point::operator/(Point const &b)
{
    Point point;

    point.x = this->x / b.x;
    point.y = this->y / b.y;
    point.z = this->z / b.z;

    return point;
}