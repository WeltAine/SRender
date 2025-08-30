#include "../../Header/Resources/Mesh.h"

/// <summary>
/// 预开辟240个顶点，80对索引
/// </summary>
Mesh::Mesh() : transform{}
{
	trangleIndexBuffer.reserve(80);
	vertexBuffer.reserve(240);
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
	this->transform.objectToWorld = m;
}

int Mesh::GetIndexSize()
{
	return vertexBuffer.size();
}
