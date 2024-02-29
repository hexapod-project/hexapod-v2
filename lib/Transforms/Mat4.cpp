#include "Mat4.h"
#include <cmath>

Mat4::Mat4()
{
    set(
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1);
}

void Mat4::set(double val)
{
    set(val, val, val, val,
        val, val, val, val,
        val, val, val, val,
        val, val, val, val);
}

void Mat4::set(Mat4 mat)
{
    set(mat.matrix[0][0], mat.matrix[0][1], mat.matrix[0][2], mat.matrix[0][3],
        mat.matrix[1][0], mat.matrix[1][1], mat.matrix[1][2], mat.matrix[1][3],
        mat.matrix[2][0], mat.matrix[2][1], mat.matrix[2][2], mat.matrix[2][3],
        mat.matrix[3][0], mat.matrix[3][1], mat.matrix[3][2], mat.matrix[3][3]);
}

void Mat4::set(double val11, double val12, double val13, double val14, double val21, double val22, double val23, double val24, double val31, double val32, double val33, double val34, double val41, double val42, double val43, double val44)
{
    //Row 1
    matrix[0][0] = val11;
    matrix[0][1] = val12;
    matrix[0][2] = val13;
    matrix[0][3] = val14;

    //Row 2
    matrix[1][0] = val21;
    matrix[1][1] = val22;
    matrix[1][2] = val23;
    matrix[1][3] = val24;

    //Row 3
    matrix[2][0] = val31;
    matrix[2][1] = val32;
    matrix[2][2] = val33;
    matrix[2][3] = val34;

    //Row 4
    matrix[3][0] = val41;
    matrix[3][1] = val42;
    matrix[3][2] = val43;
    matrix[3][3] = val44;
}

Vec4 Mat4::multiply(const Vec4 &vec)
{
    Vec4 result;

    result.x = matrix[0][0] * vec.x + matrix[0][1] * vec.y + matrix[0][2] * vec.z + matrix[0][3] * vec.w;
    result.y = matrix[1][0] * vec.x + matrix[1][1] * vec.y + matrix[1][2] * vec.z + matrix[1][3] * vec.w;
    result.z = matrix[2][0] * vec.x + matrix[2][1] * vec.y + matrix[2][2] * vec.z + matrix[2][3] * vec.w;
    result.w = matrix[3][0] * vec.x + matrix[3][1] * vec.y + matrix[3][2] * vec.z + matrix[3][3] * vec.w;

    return result;
}

Mat4 Mat4::multiply(const Mat4 &matB)
{
    double(*a)[4] = matrix;
    const double(*b)[4] = matB.matrix;

    Mat4 result;
    //Row 1
    result.matrix[0][0] = a[0][0] * b[0][0] + a[0][1] * b[1][0] + a[0][2] * b[2][0] + a[0][3] * b[3][0];
    result.matrix[0][1] = a[0][0] * b[0][1] + a[0][1] * b[1][1] + a[0][2] * b[2][1] + a[0][3] * b[3][1];
    result.matrix[0][2] = a[0][0] * b[0][2] + a[0][1] * b[1][2] + a[0][2] * b[2][2] + a[0][3] * b[3][2];
    result.matrix[0][3] = a[0][0] * b[0][3] + a[0][1] * b[1][3] + a[0][2] * b[2][3] + a[0][3] * b[3][3];

    //Row 2
    result.matrix[1][0] = a[1][0] * b[0][0] + a[1][1] * b[1][0] + a[1][2] * b[2][0] + a[1][3] * b[3][0];
    result.matrix[1][1] = a[1][0] * b[0][1] + a[1][1] * b[1][1] + a[1][2] * b[2][1] + a[1][3] * b[3][1];
    result.matrix[1][2] = a[1][0] * b[0][2] + a[1][1] * b[1][2] + a[1][2] * b[2][2] + a[1][3] * b[3][2];
    result.matrix[1][3] = a[1][0] * b[0][3] + a[1][1] * b[1][3] + a[1][2] * b[2][3] + a[1][3] * b[3][3];

    //Row 3
    result.matrix[2][0] = a[2][0] * b[0][0] + a[2][1] * b[1][0] + a[2][2] * b[2][0] + a[2][3] * b[3][0];
    result.matrix[2][1] = a[2][0] * b[0][1] + a[2][1] * b[1][1] + a[2][2] * b[2][1] + a[2][3] * b[3][1];
    result.matrix[2][2] = a[2][0] * b[0][2] + a[2][1] * b[1][2] + a[2][2] * b[2][2] + a[2][3] * b[3][2];
    result.matrix[2][3] = a[2][0] * b[0][3] + a[2][1] * b[1][3] + a[2][2] * b[2][3] + a[2][3] * b[3][3];

    //Row 4
    result.matrix[3][0] = a[3][0] * b[0][0] + a[3][1] * b[1][0] + a[3][2] * b[2][0] + a[3][3] * b[3][0];
    result.matrix[3][1] = a[3][0] * b[0][1] + a[3][1] * b[1][1] + a[3][2] * b[2][1] + a[3][3] * b[3][1];
    result.matrix[3][2] = a[3][0] * b[0][2] + a[3][1] * b[1][2] + a[3][2] * b[2][2] + a[3][3] * b[3][2];
    result.matrix[3][3] = a[3][0] * b[0][3] + a[3][1] * b[1][3] + a[3][2] * b[2][3] + a[3][3] * b[3][3];

    return result;
}

Mat4 Mat4::translate(const Vec3 &translation)
{
    Mat4 temp;
    temp.matrix[0][3] = translation.x;
    temp.matrix[1][3] = translation.y;
    temp.matrix[2][3] = translation.z;

    return multiply(temp);
}

Mat4 Mat4::rotate(double rad, const Vec3 &axis)
{
    double c = cos(rad);
    double s = sin(rad);
    double t = 1 - c;
    double x = axis.x, y = axis.y, z = axis.z;
    double tx = t * x, ty = t * y;

    Mat4 res;

    res.set(
        tx * x + c, tx * y - z * s, tx * z + y * s, 0,
        ty * x + z * s, ty * y + c, ty * z + x * s, 0,
        tx * z - y * s, ty * z + x * s, t * z * z + c, 0,
        0, 0, 0, 1);

    return multiply(res);
}

Mat4 Mat4::rotate(const Vec3 &eulerAngles)
{
    Mat4 res;
    res = res.rotate(eulerAngles.x, Vec3(1, 0, 0));
    res = res.rotate(eulerAngles.y, Vec3(0, 1, 0));
    res = res.rotate(eulerAngles.z, Vec3(0, 0, 1));

    return multiply(res);
}

Mat4 Mat4::inverse()
{
    double(*a)[4] = matrix;

    double t0 = (a[1][1] * a[2][2] * a[3][3]) + (a[1][2] * a[2][3] * a[3][1]) + (a[1][3] * a[2][1] * a[3][2]) - (a[1][3] * a[2][2] * a[3][1]) - (a[1][2] * a[2][1] * a[3][3]) - (a[1][1] * a[2][3] * a[3][2]);
    double t1 = (a[0][1] * a[2][2] * a[3][3]) + (a[0][2] * a[2][3] * a[3][1]) + (a[0][3] * a[2][1] * a[3][2]) - (a[0][3] * a[2][2] * a[3][1]) - (a[0][2] * a[2][1] * a[3][3]) - (a[0][1] * a[2][3] * a[3][2]);
    double t2 = (a[0][1] * a[1][2] * a[3][3]) + (a[0][2] * a[1][3] * a[3][1]) + (a[0][3] * a[1][1] * a[3][2]) - (a[0][3] * a[1][2] * a[3][1]) - (a[0][2] * a[1][1] * a[3][3]) - (a[0][1] * a[1][3] * a[3][2]);
    double t3 = (a[0][1] * a[1][2] * a[2][3]) + (a[0][2] * a[1][3] * a[2][1]) + (a[0][3] * a[1][1] * a[2][2]) - (a[0][3] * a[1][2] * a[2][1]) - (a[0][2] * a[1][1] * a[2][3]) - (a[0][1] * a[1][3] * a[2][2]);

    double det = a[0][0] * t0 - a[1][0] * t1 + a[2][0] * t2 - a[3][0] * t3;

    Mat4 res;

    if (det == 0)
        return res;

    double detInv = 1 / det;

    res.matrix[0][0] = t0 * detInv;
    res.matrix[0][1] = -t1 * detInv;
    res.matrix[0][2] = t2 * detInv;
    res.matrix[0][3] = -t3 * detInv;

    res.matrix[1][0] = -(a[1][0] * a[2][2] * a[3][3]) - (a[1][2] * a[2][3] * a[3][0]) - (a[1][3] * a[2][0] * a[3][2]) + (a[1][3] * a[2][2] * a[3][0]) + (a[1][2] * a[2][0] * a[3][3]) + (a[1][0] * a[2][3] * a[3][2]);
    res.matrix[1][1] = (a[0][0] * a[2][2] * a[3][3]) + (a[0][2] * a[2][3] * a[3][0]) + (a[0][3] * a[2][0] * a[3][2]) - (a[0][3] * a[2][2] * a[3][0]) - (a[0][2] * a[2][0] * a[3][3]) - (a[0][0] * a[2][3] * a[3][2]);
    res.matrix[1][2] = -(a[0][0] * a[1][2] * a[3][3]) - (a[0][2] * a[1][3] * a[3][0]) - (a[0][3] * a[1][0] * a[3][2]) + (a[0][3] * a[1][2] * a[3][0]) + (a[0][2] * a[1][0] * a[3][3]) + (a[0][0] * a[1][3] * a[3][2]);
    res.matrix[1][3] = (a[0][0] * a[1][2] * a[2][3]) + (a[0][2] * a[1][3] * a[2][0]) + (a[0][3] * a[1][0] * a[2][2]) - (a[0][3] * a[1][2] * a[2][0]) - (a[0][2] * a[1][0] * a[2][3]) - (a[0][0] * a[1][3] * a[2][2]);

    res.matrix[2][0] = (a[1][0] * a[2][1] * a[3][3]) + (a[1][1] * a[2][3] * a[3][0]) + (a[1][3] * a[2][0] * a[3][1]) - (a[1][3] * a[2][1] * a[3][0]) - (a[1][1] * a[2][0] * a[3][3]) - (a[1][0] * a[2][3] * a[3][1]);
    res.matrix[2][1] = -(a[0][0] * a[2][1] * a[3][3]) - (a[0][1] * a[2][3] * a[3][0]) - (a[0][3] * a[2][0] * a[3][1]) + (a[0][3] * a[2][1] * a[3][0]) + (a[0][1] * a[2][0] * a[3][3]) + (a[0][0] * a[2][3] * a[3][1]);
    res.matrix[2][2] = (a[0][0] * a[1][1] * a[3][3]) + (a[0][1] * a[1][3] * a[3][0]) + (a[0][3] * a[1][0] * a[3][1]) - (a[0][3] * a[1][1] * a[3][0]) - (a[0][1] * a[1][0] * a[3][3]) - (a[0][0] * a[1][3] * a[3][1]);
    res.matrix[2][3] = -(a[0][0] * a[1][1] * a[2][3]) - (a[0][1] * a[1][3] * a[2][0]) - (a[0][3] * a[1][0] * a[2][1]) + (a[0][3] * a[1][1] * a[2][0]) + (a[0][1] * a[1][0] * a[2][3]) + (a[0][0] * a[1][3] * a[2][1]);

    res.matrix[3][0] = -(a[1][0] * a[2][1] * a[3][2]) - (a[1][1] * a[2][2] * a[3][0]) - (a[1][2] * a[2][0] * a[3][1]) + (a[1][2] * a[2][1] * a[3][0]) + (a[1][1] * a[2][0] * a[3][2]) + (a[1][0] * a[2][2] * a[3][1]);
    res.matrix[3][1] = (a[0][0] * a[2][1] * a[3][2]) + (a[0][1] * a[2][2] * a[3][0]) + (a[0][2] * a[2][0] * a[3][1]) - (a[0][2] * a[2][1] * a[3][0]) - (a[0][1] * a[2][0] * a[3][2]) - (a[0][0] * a[2][2] * a[3][1]);
    res.matrix[3][2] = -(a[0][0] * a[1][1] * a[3][2]) - (a[0][1] * a[1][2] * a[3][0]) - (a[0][2] * a[1][0] * a[3][1]) + (a[0][2] * a[1][1] * a[3][0]) + (a[0][1] * a[1][0] * a[3][2]) + (a[0][0] * a[1][2] * a[3][1]);
    res.matrix[3][3] = (a[0][0] * a[1][1] * a[2][2]) + (a[0][1] * a[1][2] * a[2][0]) + (a[0][2] * a[1][0] * a[2][1]) - (a[0][2] * a[1][1] * a[2][0]) - (a[0][1] * a[1][0] * a[2][2]) - (a[0][0] * a[1][2] * a[2][1]);

    return res;
}

Vec3 Mat4::getPos()
{
    return Vec3(matrix[0][3], matrix[1][3], matrix[2][3]);
}

std::string Mat4::toString()
{
    std::string result = "[";

    for (int row = 0; row < 4; row++)
    {
        result += "[";
        for (int col = 0; col < 4; col++)
        {
            result += std::to_string(matrix[row][col]);
            if (col < 3)
                result += ", ";
        }

        result += "]";
        if (row < 3)
            result += "\n";
    }

    result += "]";

    return result;
}