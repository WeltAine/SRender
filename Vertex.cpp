#include "Vertex.h"

Vertex::Vertex()
	:position(), normal(0, 0, 0, 0), color(), uv()
{
}

Vertex::Vertex(const Vector3f& inPos, const Vector3f& inNor, const Color& inColor, const Vector2f& inUV)
	:position(inPos), normal(normal), color(inColor), uv(inUV)
{
	normal.Normalize();
	normal.w = 0;
}

Vertex::Vertex(const Vector3f& inPos, const Color& inColor, const Vector2f& inUV)
	:position(inPos), normal(0, 0, 0, 0), color(inColor), uv(inUV)
{
}

Vertex::~Vertex()
{
}

Vertex Vertex::LerpVertex(const Vertex& v1, const Vertex& v2, float t)
{
	//分歧点

	//position.z = LerpFloat(v1.position.z, v2.position.z, t);
	//color = Color::Lerp(left.color, right.color, t);
	//uv.x = LerpFloat(left.uv.x, right.uv.x, t);
	//uv.y = LerpFloat(left.uv.y, right.uv.y, t);
	//normal = left.normal + (right.normal - left.normal) * t;

	Vertex tem;
	tem.position = v1.position * (1 - t) + v2.position * t;
	tem.normal = (v1.normal * (1 - t) + v2.normal * t).Normalized();
	tem.color = v1.color * (1 - t) + v2.color * t;
	tem.uv = v1.uv * (1 - t) + v2.uv * t;
	return tem;
}

Vertex& Vertex::operator*(const Matrix& h)//一般是矩阵乘以向量，但这个使用就反过来了，最终我选择以友元的方式在Vertex中重载*运算来解决这个问题
{
	this->position = h * this->position;
	this->normal = (h * this->normal).Normalized();//这里的处理是不够的，因为对于法向量的处理是要乘以h的逆转置矩阵的//https://zhuanlan.zhihu.com/p/72734738
	//所以这个暂时只能应对均匀缩放的形变

	return *this;
}

bool Vertex::operator==(const Vertex& aim)
{

	return this->position == aim.position &&
			this->normal == aim.normal &&
			this->color == aim.color &&
			this->uv == aim.uv;
}

bool Vertex::operator<(const Vertex& aim) const
{
	return this->position.magnitude < aim.position.magnitude;//如果仅使用距离来作为象征，那么三维中一定存在一个二维是完全等价的
}

void Vertex::Print()
{
	std::cout << "Vector3f: " << this->position.x << " " << this->position.y << " " << this->position.z;
	std::cout << " Color: " << this->color.r << " " << this->color.g << " " << this->color.b << std::endl;

}


//友元函数，实现M * V，而不是V * M
Vertex& operator*(Matrix& leftMatrix, Vertex& rightVertex)//！自添
{
	return rightVertex* leftMatrix;
}
