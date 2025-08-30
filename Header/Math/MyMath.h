#pragma once

#include "Vector.h"
#define PI 3.1415926535

float Clamp(float value, float min, float max);


/// <summary>
/// 该方法可对任意三角面进行重心插值
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <param name="v3"></param>
/// <param name="p">基于该参数的x,y进行插值，但是不会去验证该参数是否共面</param>
/// <returns>返回一个与p同xy且共面的插值系数</returns>
Vector3f CenterOfGravityInterpolation(Vector3f v1, Vector3f v2, Vector3f v3, Vector3f p);

float LerpFloat(float f1, float f2, float t);
