#pragma once

#include "Vector.h"
#define PI 3.1415926535

float Clamp(float value, float min, float max);

Vector3f CenterOfGravity_Projector(Vector3f v1, Vector3f v2, Vector3f v3, Vector3f p);

float LerpFloat(float f1, float f2, float t);
