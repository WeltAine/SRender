#pragma once
#include "Matrix.h"
#include "Vector.h"
#include "Camera.h"

class Light : public Camera {


public:
	float intensity;

	Light(Camera lightCamera = { {}, false, 1, 1, 50, 84.3 }, float intensity = 1)
		: Camera{ lightCamera }, intensity{ intensity }
	{
		//delete[] this->cBuffer;
		//this->cBuffer = nullptr;
	}


	virtual void UpdateLight(const Transform& t, float aspect, float nearPlane, float farPlane, float fov, float intensity, bool isPerspective) = 0;

};

//直线光
class DirectionLight : public Light{

public:

	//bool forVertex;//?是逐顶点还是逐像素，暂时还不知道怎么用

	DirectionLight(Camera lightCamera = { {}, false, 1, 1, 50, 168.6 }, float intensity = 1)
		: Light{ lightCamera, intensity }
	{};
	//DirectionLight(const Vector3f& pos, const Vector3f& dir, float i, bool forV = true);
	//？为什么没有重定义问题，因为类内部的方法定义，会带有隐式inline
	~DirectionLight();

	Vector3f GetDirection(Vector3f aimPos = Vector3f(0, 0, 0)) const;
	//Matrix LookAt(const Vector3f& upAxis) const;//将光源转换到世界原点的V矩阵，应该是用于阴影的

	void UpdateLight(const Transform& t, float aspect, float nearPlane, float farPlane, float fov, float intensity, bool isPerspective) override;

};


//!!!暂时不使用该类
class PointLight : public Light{

public :

	//bool forVertex;//原项目没有给这个类配置，感觉一些原本该配置的都没配置，是不是这个类只是写着，就没用过


	PointLight(Camera lightCamera, float intensity)
		: Light{ lightCamera, intensity } {};
	//PointLight(const Vector3f& pos, float i)
	//	:position{ pos }, intensity{i} {};
	~PointLight() {};

	Vector3f GetDirection(const Vector3f& aimPos) const;
};


//？为什么没有触发类的重定义，首先对于同一个编译单元，我们的“类定义”写在了同文件里，有头文件保护防止重复展开
//其次，“类定义”（如 class Transform { ... };）本质上是类型声明，告诉编译器类的结构信息（成员变量、函数等）。仅声明类型结构，不会在目标文件（.o 或 .obj）中生成可链接的符号。

