#pragma once
#include "Matrix.h"
#include "Vector.h"

//直线光
class DirectionLight {

public:
	Vector3f position, direction;//位置，方向//？方相光要位置干嘛，点光源还好说，看看之后怎么用吧
	float intensity;

	bool forVertex;//?是逐顶点还是逐像素，暂时还不知道怎么用

	DirectionLight();
	DirectionLight(const Vector3f& pos, const Vector3f& dir, float i, bool forV = true);
	//？为什么没有重定义问题，因为类内部的方法定义，会带有隐式inline
	~DirectionLight();

	Vector3f GetDirection(Vector3f aimPos = Vector3f(0, 0, 0)) const;
	Matrix LookAt(const Vector3f& upAxis) const;//将光源转换到世界原点的V矩阵，应该是用于阴影的

};

class PointLight {

public :
	Vector3f position;
	float intensity;


	//bool forVertex;//原项目没有给这个类配置，感觉一些原本该配置的都没配置，是不是这个类只是写着，就没用过


	PointLight()
		:position{}, intensity{1} {};
	PointLight(const Vector3f& pos, float i)
		:position{ pos }, intensity{i} {};
	~PointLight() {};

	Vector3f GetDirection(const Vector3f& aimPos) const;
};


//？为什么没有触发类的重定义，首先对于同一个编译单元，我们的“类定义”写在了同文件里，有头文件保护防止重复展开
//其次，“类定义”（如 class Transform { ... };）本质上是类型声明，告诉编译器类的结构信息（成员变量、函数等）。仅声明类型结构，不会在目标文件（.o 或 .obj）中生成可链接的符号。

