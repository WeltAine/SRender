#include "Renderer.h"
#include "MyMath.h"

Renderer::Renderer(HDC inScreenHDC, int inDeviceWidth, int inDeviceHeight, Camera* cam)
	: screenHDC(inScreenHDC), deviceWidth(inDeviceWidth), deviceHeight(inDeviceHeight), camera(cam)
{

	texture = new Texture();
	texture->LoadTexture("");//！！！纹理路径，记得填

}


Renderer::~Renderer()
{

}

void Renderer::DrawMesh(Mesh& aimMesh, IShader* shader, DepthBuffer* zBuffer)
{
	if (aimMesh.vertexBuffer.size() > 0) {

		DrawByIndex(aimMesh, shader, zBuffer);

	}
	return;
}



void Renderer::DrawByIndex(Mesh& aimMesh, IShader* shader, DepthBuffer* zBuffer)
{
	//for (int i = 0; i < aimMesh.vertexBuffer.size(); i += 3) {

	//	Vertex& v0 = aimMesh.vertexBuffer[i];
	//	Vertex& v1 = aimMesh.vertexBuffer[i + 1];
	//	Vertex& v2 = aimMesh.vertexBuffer[i + 2];

	//	RasterizeTrangle(v0, v1, v2, shader, zBuffer);
	//}


	for (int i = 0; i < aimMesh.trangleIndexBuffer.size(); i++) {

		Vertex& v0 = aimMesh.vertexBuffer[aimMesh.trangleIndexBuffer[i].x];
		Vertex& v1 = aimMesh.vertexBuffer[aimMesh.trangleIndexBuffer[i].y];
		Vertex& v2 = aimMesh.vertexBuffer[aimMesh.trangleIndexBuffer[i].z];

		RasterizeTrangle(v0, v1, v2, shader, zBuffer);
	}



}

void Renderer::RasterizeTrangle(Vertex& v0, Vertex& v1, Vertex& v2, IShader* shader, DepthBuffer* zBuffer)
{

	Vertex _v0 = v0, _v1 = v1, _v2 = v2;

	shader->VS(_v0, _v1, _v2);//以完成mvp与标准化，并且完成了绘制上下三角形所需的排序//参数会同步改变


	//视口空间（NCP）转换为屏幕空间（zBuffer的屏幕空间）//但这一次Uniform不会同步
	PrepareRasterization(_v0, zBuffer);
	PrepareRasterization(_v1, zBuffer);
	PrepareRasterization(_v2, zBuffer);


	if (_v2.position.y == _v1.position.y) {

		DrawBottomTriangle(_v0, _v1, _v2, shader, zBuffer, _v1);

	}
	else if (_v0.position.y == _v1.position.y) {

		DrawTopTriangle(_v0, _v1, _v2, shader, zBuffer, _v0);

	}
	else {

		float m = (_v2.position.y - _v1.position.y) / (_v2.position.y - _v0.position.y);
		float n = m * _v2.position.z / ((1 - m) * _v0.position.y + m * _v2.position.z);
		Vertex _v = Vertex::LerpVertex(_v2, _v0, n);

		DrawTopTriangle(_v0, _v1, _v2, shader, zBuffer, _v);
		DrawBottomTriangle(_v0, _v1, _v, shader, zBuffer, _v);

	}

	

}

//对参数同步改变
void Renderer::PrepareRasterization(Vertex& vertex, DepthBuffer* zBuffer)
{
	vertex.position.x = ((vertex.position.x + 1.0f) / 2) * zBuffer->width;
	vertex.position.y = ((vertex.position.y + 1.0f) / 2) * zBuffer->height;

}

void Renderer::DrawTopTriangle(Vertex& v0, Vertex& v1, Vertex& v2, IShader* shader, DepthBuffer* zBuffer, Vertex& interpolateVertex)
{
	if (abs(v1.position.y - v2.position.y) < 1) {
		return;
	}

	for (int y = interpolateVertex.position.y + 0.5; y <= int(v2.position.y - 0.5); y++) {

		float n = (v2.position.y - y) / (v2.position.y - interpolateVertex.position.y);
		Vertex temVertex_1 = Vertex::LerpVertex(v2, v1, n);
		Vertex temVertex_2 = Vertex::LerpVertex(v2, interpolateVertex, n);
		//这些点的位置未经过矫正，只有xy是正确的


		DrawLine(temVertex_1, temVertex_2, shader, zBuffer, v0.position, v1.position, v2.position);

	}
}

void Renderer::DrawBottomTriangle(Vertex& v0, Vertex& v1, Vertex& v2, IShader* shader, DepthBuffer* zBuffer, Vertex& interpolateVertex)
{
	if (abs(v1.position.y - v0.position.y) < 1) {
		return;
	}

	for (int y = interpolateVertex.position.y - 0.5; y >= int(v0.position.y + 0.5); y--) {

		float n = (v0.position.y - y) / (v0.position.y - interpolateVertex.position.y);
		Vertex temVertex_1 = Vertex::LerpVertex(v0, v1, n);
		Vertex temVertex_2 = Vertex::LerpVertex(v0, interpolateVertex, n);
		//这些点的位置未经过矫正，只有xy是正确的


		DrawLine(temVertex_1, temVertex_2, shader, zBuffer, v0.position, v1.position, v2.position);

	}
}

void Renderer::DrawLine(Vertex& aimVertex_1, Vertex& aimVertex_2, IShader* shader, DepthBuffer* zBuffer, Vector3f& v0, Vector3f& v1, Vector3f& v2)
{
	Vertex leftVertex = (aimVertex_1.position.x > aimVertex_2.position.x) ? aimVertex_1 : aimVertex_2;
	Vertex rightVertex = (aimVertex_1.position.x > aimVertex_2.position.x) ? aimVertex_2 : aimVertex_1;

	leftVertex.position.x = int(leftVertex.position.x + 0.5);
	rightVertex.position.x = int(rightVertex.position.x - 0.5);
	//这条直线间就是可着色范围（包括端点），两者刚好对应两个在位图中的像素索引

	if (abs(leftVertex.position.x - rightVertex.position.x) < 1) {
		return;
	}

	for (int x = leftVertex.position.x; x <= rightVertex.position.x; x++) {
		Vertex rendererVertex;
		rendererVertex.position.x = x; rendererVertex.position.y = leftVertex.position.y;
		Vector3f interpolation = CenterOfGravity_Projector(v0, v1, v2, rendererVertex.position);

		//虽然FS中的Uniform还停留在MVP这个阶段，但没关系，因为质心坐标才是最重要的
		if (shader->FS(rendererVertex, interpolation))
			//产生必要的插值信息与最终该像素的颜色结果，并且确定是否在某个光源的阴影纹理中可见（就我了解的FS，这里它明显承担了一部分三角形遍历和设置的工作)
		{
			float depth = (rendererVertex.position.z + 1.0f) / 2;//将Z调整到0与1之间
			if (ZTestAndWrite(rendererVertex.position.x, rendererVertex.position.y, depth, zBuffer))//！！！我突然意识到一个事情，这里的zBuffer真的是用来确定遮挡关系的，但Shader中的那个确实光源的
			{
				if (dynamic_cast<PhongShader*>(shader)) {//PhongShader才允许执行对位图设置像素的功能

					DrawPixel((rendererVertex.position.x / zBuffer->width) * this->deviceWidth, (rendererVertex.position.y / zBuffer->height) * this->deviceHeight, rendererVertex.color);//记得从纹理的屏幕坐标映射回设备屏幕坐标

				}
			}
		}
	}
}

void Renderer::DrawPixel(int x, int y, Color color)
{
	SetPixel(screenHDC, x, y, RGB(255 * color.r, 255 * color.g, 255 * color.b));
}

bool Renderer::ZTestAndWrite(int x, int y, float depth, DepthBuffer* zbuffer)
{
	if (zbuffer->Sample(x, y) > depth) {
		int index = y * zbuffer->width + x;
		zbuffer->depthBuffer[index];
		return true;
	}

	return false;
}

void Renderer::Clear(DepthBuffer* buffer)
{
	for (int y = 0; y < buffer->height; y++) {
		for (int x = 0; x < buffer->width; x++) {
			buffer->depthBuffer[y * buffer->width + x] = 1;
		}
	}

}



