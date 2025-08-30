#pragma once

#include "Vector.h"
#define PI 3.1415926535

float Clamp(float value, float min, float max);


/// <summary>
/// �÷����ɶ�����������������Ĳ�ֵ
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <param name="v3"></param>
/// <param name="p">���ڸò�����x,y���в�ֵ�����ǲ���ȥ��֤�ò����Ƿ���</param>
/// <returns>����һ����pͬxy�ҹ���Ĳ�ֵϵ��</returns>
Vector3f CenterOfGravityInterpolation(Vector3f v1, Vector3f v2, Vector3f v3, Vector3f p);

float LerpFloat(float f1, float f2, float t);
