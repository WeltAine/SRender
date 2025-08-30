#include "../../Header/Resources/Vertex.h"

Vertex::Vertex()
	:position(), normal(0, 0, 0, 0), color(), uv()
{
}


/// <summary>
/// inPosԭ����¼��inNor���Լ�����һ����������֤w = 0
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
/// inPosԭ����¼��0��������
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
/// ��v1��v2֮�䣬�Ը������Զ�֮��t%λ���ϵ�ֵ
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
/// �����ֱ��д��this��ע�ⲻҪ�ø÷��������Ǿ��ȱ仯��ƽ���ǿ��Եģ�
/// </summary>
/// <param name="h"></param>
/// <returns></returns>
Vertex& Vertex::operator*(const Matrix& h)//һ���Ǿ�����������������ʹ�þͷ������ˣ�������ѡ������Ԫ�ķ�ʽ��Vertex������*����������������
{
	this->position = h * this->position;
	this->normal = (h * this->normal).Normalized();//����Ĵ����ǲ����ģ���Ϊ���ڷ������Ĵ�����Ҫ����h����ת�þ����//https://zhuanlan.zhihu.com/p/72734738
	//���������ʱֻ��Ӧ�Ծ������ţ���ת��ƽ�Ƶ��α�

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
	//return this->position.magnitude < aim.position.magnitude;//�����ʹ�þ�������Ϊ��������ô��ά��һ������һ����ά����ȫ�ȼ۵�

	//��ȡ������Ͱ������뷨�������8ά��Ϣ���бȽ� 
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

///�����ֱ��д��this
//��Ԫ������ʵ��M * V��������V * M
Vertex& operator * (Matrix& leftMatrix, Vertex& rightVertex)
{
	return rightVertex * leftMatrix;
}
