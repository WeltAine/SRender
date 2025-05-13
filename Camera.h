#pragma once

#include "Transform.h"
#include "Matrix.h"

class Camera {

public:
	Transform transform;//！！这个成员几乎没用
	Matrix v, p;//得到了一个[-1. 1]的三次方的立方体

	Camera(const Transform& t) :transform{ t }, v{}, p{} {};
	~Camera() {};


	//View矩阵计算
	Matrix LookAt(const Vector3f& eyePos, const Vector3f& lookDir, const Vector3f& upAxis);

	//Perspective矩阵计算
	Matrix Perspective(float fov, float aspect, float nearPlane, float farPlane);//参数为垂直仰角(角度质)（全的），视口比例（长/宽）， 近平面距离，远平面距离
	//？原项目中后两个函数看起来是返回vp而不是只有p，所以它们使用前不需要LookAt去变换空间。但是我还是只返回p//之后看吧，要不要改
	Matrix Perspective(float l, float r, float t, float b, float n, float f);
	Matrix Orthographic(float l, float r, float t, float b, float n, float f);



};