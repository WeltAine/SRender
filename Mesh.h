#pragma once

#include "Transform.h"
#include "Vertex.h"
#include <vector>

//模型的Mesh网格
class Mesh {

public:
	Transform transform;

	//！魔改
	//std::vector<Vector3f> positionBuffer;
	//std::vector<Vector3f> normalBuffer;
	//std::vector<Vector2f> uvBuffer;
	//？只有一个Vertex列表不行么，为什么还要这三个
	std::vector<Vertex> vertexBuffer;//！顶点（这是自添）
	//std::vector<Vector3i> indexBuffer;//组合索引， ？看了源码，一个Vector3i里头是位置，uv， 法线
	std::vector<Vector3i> trangleIndexBuffer;//！魔改

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