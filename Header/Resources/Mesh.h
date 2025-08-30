#pragma once

#include "Transform.h"
#include "Vertex.h"
#include <vector>

//ģ�͵�Mesh����
class Mesh {

public:
	Transform transform;//�������Ҳ����ζ��meshҲ��object

	std::vector<Vertex> vertexBuffer;//����
	std::vector<Vector3i> trangleIndexBuffer;//λ�ã�uv�� ����

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