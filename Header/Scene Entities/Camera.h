#pragma once

#include "../Resources/Transform.h"
#include "../Math/Matrix.h"
#include <tuple>
#include <memory>
//#include "Buffer.h"

struct DepthBuffer;
struct ColorBuffer;

class Camera {

public:
	Transform transform;//以其Z作为向前方向
	float aspect, nearPlane, farPlane, fov;
	Matrix v, p;//得到一个[-1. 1]的三次方的立方体
	bool isPerspective = true;

	std::shared_ptr<DepthBuffer> zBuffer;
	std::shared_ptr<ColorBuffer> cBuffer;


	/// <summary>
	/// 构造相机
	/// </summary>
	/// <param name="t">transform</param>
	/// <param name="isPerspective">mode</param>
	/// <param name="aspect">比例</param>
	/// <param name="nearPlane">近平面</param>
	/// <param name="farPlane">远平面</param>
	/// <param name="fov">视锥垂直夹角</param>
	Camera(const Transform& t, bool isPerspective, float aspect, float nearPlane, float farPlane, float fov);


	~Camera() {
	};

	void UpdateCamera(const Transform& t, bool isPerspective, float aspect, float nearPlane, float farPlane, float fov);

	//View矩阵计算
	Matrix LookAt(const Vector3f& eyePos, const Vector3f& lookDir, const Vector3f& upAxis);

	//Perspective矩阵计算
	Matrix Perspective(float fov, float aspect, float nearPlane, float farPlane);//参数为视锥垂直夹角(角度质)，视口比例（宽/高）， 近平面距离，远平面距离
	Matrix Perspective(float l, float r, float t, float b, float n, float f);
	Matrix Orthographic(float l, float r, float t, float b, float n, float f);
	Matrix Orthographic(float fov, float aspect, float nearPlane, float farPlane);


};
