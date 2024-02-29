#ifndef Mat4_H
#define Mat4_H

#include "Vec3.h"
#include "Vec4.h"
#include <string>

class Mat4
{
public:
    // Matrix[Row][Col]
    double matrix[4][4];

    Mat4();
    void set(double val11, double val12, double val13, double val14, double val21, double val22, double val23, double val24, double val31, double val32, double val33, double val34, double val41, double val42, double val43, double val44);
    void set(double val);
    void set(Mat4 mat);
    Vec4 multiply(const Vec4 &vec);
    Mat4 multiply(const Mat4 &matB);
    Mat4 translate(const Vec3 &translation);
    Mat4 rotate(double rad, const Vec3 &axis);
    Mat4 rotate(const Vec3 &eulerAngles);
    Mat4 inverse();
    Vec3 getPos();
    std::string toString();
};

#endif