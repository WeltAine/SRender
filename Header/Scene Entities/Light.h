#pragma once
#include "Camera.h"

class Light : public Camera {

public:
	float intensity;

	Light(const Camera& lightCamera, float intensity = 1);

	virtual void UpdateLight(const Transform& t, float aspect, float nearPlane, float farPlane, float fov, float intensity, bool isPerspective) = 0;

};

//直线光
class DirectionLight : public Light{

public:

	DirectionLight(const Camera& lightCamera = { {}, false, 1, 1, 50, 168.6 }, float intensity = 1)
		: Light{ lightCamera, intensity }
	{};
	//DirectionLight(const Vector3f& pos, const Vector3f& dir, float i, bool forV = true);
	//？为什么没有重定义问题，因为类内部的方法定义，会带有隐式inline
	~DirectionLight();

	Vector3f GetDirection(Vector3f aimPos = Vector3f(0, 0, 0)) const;

	void UpdateLight(const Transform& t, float aspect, float nearPlane, float farPlane, float fov, float intensity, bool isPerspective) override;

};


//点光源
class PointLight : public Light{

public :

	PointLight(const Camera& lightCamera = { {}, false, 1, 1, 50, 168.6 }, float intensity = 1)
		: Light{ lightCamera, intensity } {};

	~PointLight() {};

	Vector3f GetDirection(const Vector3f& aimPos) const;

	void UpdateLight(const Transform& t, float aspect, float nearPlane, float farPlane, float fov, float intensity, bool isPerspective) override;
};


//？为什么没有触发类的重定义，首先对于同一个编译单元，我们的“类定义”写在了头文件里，有头文件保护防止重复展开
//其次，“类定义”（如 class Transform { ... };）本质上是类型声明，告诉编译器类的结构信息（成员变量、函数等）。仅声明类型结构，不会在目标文件（.o 或 .obj）中生成可链接的符号。

