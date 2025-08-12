#pragma once

#include "Transform.h"
#include "Matrix.h"
#include <tuple>
#include <memory>
//#include "Buffer.h"

struct DepthBuffer;
struct ColorBuffer;

class Camera {

public:
	Transform transform;//！！这个成员几乎没用//以其Z作为向前方向
	float aspect, nearPlane, farPlane, fov;
	Matrix v, p;//得到了一个[-1. 1]的三次方的立方体
	bool isPerspective = true;

	std::shared_ptr<DepthBuffer> zBuffer;
	std::shared_ptr<ColorBuffer> cBuffer;

	Camera(const Transform& t, bool isPerspective, float aspect, float nearPlane, float farPlane, float fov);
	//	:
	//	transform{ t }, 
	//	v{LookAt(t.position, t.zAxis, t.yAxis)}, 
	//	p{isPerspective ? Perspective(fov, aspect, nearPlane, farPlane) : Orthographic(fov, aspect, nearPlane, farPlane)} {
	//
	//	this->aspect = aspect;
	//	this->nearPlane = nearPlane;
	//	this->farPlane = farPlane;
	//	this->fov = fov;
	//	this->isPerspective = isPerspective;

	//	cBuffer = new ColorBuffer{512, int(512 * aspect), this};
	//	zBuffer = new DepthBuffer{512, int(512 * aspect), this};

	//	//cBuffer->aimCamera = this;
	//	//zBuffer->aimCamera = this;
	//};



	~Camera() {
		//if(zBuffer != nullptr)
		//	delete[] zBuffer;
		//if(cBuffer != nullptr)
		//	delete[] cBuffer;
	};

	void UpdateCamera(const Transform& t, bool isPerspective, float aspect, float nearPlane, float farPlane, float fov);

	//View矩阵计算
	Matrix LookAt(const Vector3f& eyePos, const Vector3f& lookDir, const Vector3f& upAxis);

	//Perspective矩阵计算
	Matrix Perspective(float fov, float aspect, float nearPlane, float farPlane);//参数为垂直仰角(角度质)（全的），视口比例（宽/高）， 近平面距离，远平面距离
	//？原项目中后两个函数看起来是返回vp而不是只有p，所以它们使用前不需要LookAt去变换空间。但是我还是只返回p//之后看吧，要不要改
	Matrix Perspective(float l, float r, float t, float b, float n, float f);
	Matrix Orthographic(float l, float r, float t, float b, float n, float f);
	Matrix Orthographic(float fov, float aspect, float nearPlane, float farPlane);


};
