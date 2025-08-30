#pragma once

#include "Transform.h"
#include "Vertex.h"
#include <vector>

//模型的Mesh网格
class Mesh {

public:
	Transform transform;//这个属性也就意味着mesh也是object

	std::vector<Vertex> vertexBuffer;//顶点
	std::vector<Vector3i> trangleIndexBuffer;//位置，uv， 法线

	Mesh();
	~Mesh();

	void AddVertexData(const Vertex& v);
	void AddVertexData(const Vector3f& pos, const Vector3f& nor, const Color& col, const Vector2f& uv);
	void AddVertexData(const Vector3f& pos, const Color& col, const Vector2f& uv);

	Transform GetTransform();
	void SetTransform(const Transform& t);

	Matrix GetObjectToWorld();
	void SetObjectToWorld(const Matrix& m);
	
	int GetIndexSize();

};