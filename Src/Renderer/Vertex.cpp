#include "../../Header/Resources/Vertex.h"

Vertex::Vertex()
	:position(), normal(0, 0, 0, 0), color(), uv()
{
}


/// <summary>
/// inPos原样记录，inNor会自己做归一化处理，并保证w = 0
/// </summary>
/// <param name="inPos"></param>
/// <param name="inNor"></param>
/// <param name="inColor"></param>
/// <param name="inUV"></param>
Vertex::Vertex(const Vector3f& inPos, const Vector3f& inNor, const Color& inColor, const Vector2f& inUV)
	:position(inPos), normal(inNor), color(inColor), uv(inUV)
{
	normal.Normalize();
	normal.w = 0;
}

/// <summary>
/// inPos原样记录，0向量法线
/// </summary>
/// <param name="inPos"></param>
/// <param name="inColor"></param>
/// <param name="inUV"></param>
Vertex::Vertex(const Vector3f& inPos, const Color& inColor, const Vector2f& inUV)
	:position(inPos), normal(0, 0, 0, 0), color(inColor), uv(inUV)
{
}

Vertex::~Vertex()
{
}


/// <summary>
/// 在v1与v2之间，对各个属性对之间t%位置上的值
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <param name="t"></param>
/// <returns></returns>
Vertex Vertex::LerpVertex(const Vertex& v1, const Vertex& v2, float t)
{

	Vertex tem;
	tem.position = v1.position * (1 - t) + v2.position * t;
	tem.normal = (v1.normal * (1 - t) + v2.normal * t).Normalized();
	tem.color = v1.color * (1 - t) + v2.color * t;
	tem.uv = v1.uv * (1 - t) + v2.uv * t;
	return tem;
}


/// <summary>
/// 结果会直接写入this，注意不要用该方法发生非均匀变化（平移是可以的）
/// </summary>
/// <param name="h"></param>
/// <returns></returns>
Vertex& Vertex::operator*(const Matrix& h)//一般是矩阵乘以向量，但这个使用就反过来了，最终我选择以友元的方式在Vertex中重载*运算来解决这个问题
{
	this->position = h * this->position;
	this->normal = (h * this->normal).Normalized();//这里的处理是不够的，因为对于法向量的处理是要乘以h的逆转置矩阵的//https://zhuanlan.zhihu.com/p/72734738
	//所以这个暂时只能应对均匀缩放，旋转和平移的形变

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
	//return this->position.magnitude < aim.position.magnitude;//如果仅使用距离来作为象征，那么三维中一定存在一个二维是完全等价的

	//采取类似于桶排序的想法，对这个8维信息进行比较 
	return (this->position.x != aim.position.x) ? (this->position.x < aim.position.x) :
		(this->position.y != aim.position.y) ? (this->position.y < aim.position.y) :
		(this->position.z != aim.position.z) ? (this->position.z < aim.position.z) :
		(this->normal.x != aim.normal.x) ? (this->normal.x < aim.normal.x) :
		(this->normal.y != aim.normal.y) ? (this->normal.y < aim.normal.y) :
		(this->normal.z != aim.normal.z) ? (this->normal.z < aim.normal.z) :
		(this->uv.x != aim.uv.x) ? (this->uv.x < aim.uv.x) :
		(this->uv.y < aim.uv.y);
}

void Vertex::Print()
{
	std::cout << "Vector3f: " << this->position.x << " " << this->position.y << " " << this->position.z;
	std::cout << " Color: " << this->color.r << " " << this->color.g << " " << this->color.b << std::endl;

}

///结果会直接写入this
//友元函数，实现M * V，而不是V * M
Vertex& operator * (Matrix& leftMatrix, Vertex& rightVertex)
{
	return rightVertex * leftMatrix;
}
