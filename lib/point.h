#ifndef Point_H
#define Point_H

class Point
{
private:
    double x;
    double y;
    double z;

public:
    Point();
    Point(double x);
    Point(double x, double y);
    Point(double x, double y, double z);
    double getX();
    double getY();
    double getZ();
    double getDistance(Point const& b);
    Point operator-(Point const& b);
    Point operator+(Point const& b);
    Point operator*(Point const& b);
    Point operator/(Point const& b);
};

#endif