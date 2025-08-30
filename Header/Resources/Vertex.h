#pragma once

#include "../Math/Matrix.h"
#include "../Math/Vector.h"
#include "Color.h"
#include "../Math/MyMath.h"

class Vertex {
public:
	friend Vertex& operator * (Matrix& leftMatrix, Vertex& rightVertex);
	

public:
	Vector3f position, normal;
	Color color;
	Vector2f uv;

	Vertex();
	Vertex(const Vector3f& inPos, const Vector3f& inNor, const Color& inColor, const Vector2f& inUV);
	Vertex(const Vector3f& inPos, const Color& inColor, const Vector2f& inUV);
	~Vertex();


	//void LerpVertex(const Vertex& v1, const Vertex& v2, float t);//为什么这样设计，改变发起对象，而不是返回一个结果
	static Vertex LerpVertex(const Vertex& v1, const Vertex& v2, float t);

	Vertex& operator * (const Matrix& h);//这里对使用者而言，可能是M， MV， P

	bool operator == (const Vertex& aim);
	bool operator < (const Vertex& aim) const;//必须声明为const

	void Print();

};

Vertex& operator * (Matrix& leftMatrix, Vertex& rightVertex);