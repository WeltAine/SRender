#include "../../Header/Math/MyMath.h"
//#include <math.h>


float Clamp(float value, float min, float max)
{
    return (value <= min) ? min : (value > max) ? max : value;

}


/// <summary>
/// 该方法可对任意三角面进行重心插值
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <param name="v3"></param>
/// <param name="p">基于该参数的x,y进行插值，但是不会去验证该参数是否共面</param>
/// <returns>返回一个与p同xy且共面的插值系数</returns>
Vector3f CenterOfGravityInterpolation(Vector3f v1, Vector3f v2, Vector3f v3, Vector3f p)
{
    //p = alpha * v1 + beta * v2 + gamma * v3;
    float alphaMolecules = (v1.x - v3.x) * (v2.y - v3.y) - (v1.y - v3.y) * (v2.x - v3.x);
    float betaMoulecules = (v2.x - v3.x) * (v1.y - v3.y) - (v2.y - v3.y) * (v1.x - v3.x);

    if (alphaMolecules == 0)
        return Vector3f(-1, -1, -1);
    if (betaMoulecules == 0)
        return Vector3f(-1, -1, -1);

    float alpha = ((p.x - v3.x) * (v2.y - v3.y) - (p.y - v3.y) * (v2.x - v3.x)) / alphaMolecules;
    float beta = ((p.x - v3.x) * (v1.y - v3.y) - (p.y - v3.y) * (v1.x - v3.x)) / betaMoulecules;
    float gamma = 1 - alpha - beta;

    return Vector3f(alpha, beta, gamma);
}

float LerpFloat(float f1, float f2, float t) {
    return f1 * (1 - t) + f2 * t;
}
