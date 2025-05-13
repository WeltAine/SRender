#pragma once

#include "Vertex.h"
#include "Light.h"
#include "Texture.h"
#include "Camera.h"
#include"Shader.h"
#include "Mesh.h"
#include "Buffer.h"

class Renderer {

public:

	Camera* camera;
	std::vector<DirectionLight> directionLights;//！！在Uniform中重复存在，且该类的任何一个位置都没有使用它们
	std::vector<PointLight> pointLights;//！！在Uniform中重复存在，且该类的任何一个位置都没有使用它们
	Texture* texture;

	HDC screenHDC;
	int deviceWidth, deviceHeight;


public:

	Renderer(HDC inScreenHDC, int inDeviceWidth, int inDeviceHeight, Camera* cam);
	~Renderer();

	void DrawMesh(Mesh& aimMesh, IShader* shader, DepthBuffer* zBuffer);//这个DepthBuffer会沿着调用链一直向下传递，直到 ZTestAndWrite这里才会被使用，被更改
	void DrawByIndex(Mesh& aimMesh, IShader* shader, DepthBuffer* zBuffer);
	void RasterizeTrangle(Vertex& v0, Vertex& v1, Vertex& v2, IShader* shader, DepthBuffer* zBuffer);
	void PrepareRasterization(Vertex& vertex, DepthBuffer* zBuffer);
	void DrawTopTriangle(Vertex& v0, Vertex& v1, Vertex& v2, IShader* shader, DepthBuffer* zBuffer, Vertex& interpolateVertex);
	void DrawBottomTriangle(Vertex& v0, Vertex& v1, Vertex& v2, IShader* shader, DepthBuffer* zBuffer, Vertex& interpolateVertexv);
	void DrawLine(Vertex& aimVertex_1, Vertex& aimVertex_2, IShader* shader, DepthBuffer* zBuffer, Vector3f& v0, Vector3f& v1, Vector3f& v2);
	void DrawPixel(int x, int y, Color color);

	bool ZTestAndWrite(int x, int y, float depth, DepthBuffer* zbuffer);

	void Clear(DepthBuffer* buffer);

};
