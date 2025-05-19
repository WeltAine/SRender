#include "Mesh.h"

Mesh::Mesh()
{
	trangleIndexBuffer.reserve(500);
	vertexBuffer.reserve(1500);
}

Mesh::~Mesh()
{
}

void Mesh::AddVertexData(const Vertex& v)
{
	vertexBuffer.emplace_back(v);
}

void Mesh::AddVertexData(const Vector3f& pos, const Vector3f& nor, const Color& col, const Vector2f& uv)
{
	vertexBuffer.emplace_back(pos, nor, col, uv);
}

void Mesh::AddVertexData(const Vector3f& pos, const Color& col, const Vector2f& uv)
{
	vertexBuffer.emplace_back(pos, col, uv);
}

Transform Mesh::GetTransform()
{
	return this->transform;
}

void Mesh::SetTransform(const Transform& t)
{
	this->transform = t;
}

Matrix Mesh::GetObjectToWorld()
{
	return this->transform.objectToWorld;
}

void Mesh::SetObjectToWorld(const Matrix& m)
{
	this->transform.objectToWorld = m;//感觉不妥，不知道作者实际上是否真的用过该函数
}

int Mesh::GetIndexSize()
{
	return vertexBuffer.size();
}
