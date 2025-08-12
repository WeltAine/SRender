#include "Renderer.h"
#include "MyMath.h"

#include <iostream>
#include "libbmp.h"

namespace ordRender {
	//Renderer::Renderer(HDC inScreenHDC, int inDeviceWidth, int inDeviceHeight, Camera* cam)
	//	: screenHDC(inScreenHDC), deviceWidth(inDeviceWidth), deviceHeight(inDeviceHeight), camera(cam)
	//{

	//	//看了一眼引用，完全没用到过
	//	//texture = new Texture();
	//	//texture->LoadTexture("gezi.bmp");//！！！纹理路径，记得填

	//}


	//Renderer::~Renderer()
	//{

	//}

	//void Renderer::DrawMesh(Mesh& aimMesh, IShader* shader, DepthBuffer* zBuffer)
	//{
	//	if (aimMesh.vertexBuffer.size() > 0) {

	//		DrawByIndex(aimMesh, shader, zBuffer);

	//	}
	//	return;
	//}



	//void Renderer::DrawByIndex(Mesh& aimMesh, IShader* shader, DepthBuffer* zBuffer)
	//{
	//	//for (int i = 0; i < aimMesh.vertexBuffer.size(); i += 3) {

	//	//	Vertex& v0 = aimMesh.vertexBuffer[i];
	//	//	Vertex& v1 = aimMesh.vertexBuffer[i + 1];
	//	//	Vertex& v2 = aimMesh.vertexBuffer[i + 2];

	//	//	RasterizeTrangle(v0, v1, v2, shader, zBuffer);
	//	//}


	//	for (int i = 0; i < aimMesh.trangleIndexBuffer.size(); i++) {

	//		Vertex& v0 = aimMesh.vertexBuffer[aimMesh.trangleIndexBuffer[i].x];
	//		Vertex& v1 = aimMesh.vertexBuffer[aimMesh.trangleIndexBuffer[i].y];
	//		Vertex& v2 = aimMesh.vertexBuffer[aimMesh.trangleIndexBuffer[i].z];

	//		RasterizeTrangle(v0, v1, v2, shader, zBuffer);


	//		{

	//			BmpImg img(1000, 1000);

	//			for (int y = 0, x; y < 1000; y++)
	//			{
	//				for (x = 0; x < 1000; x++)
	//				{
	//					float _color = zBuffer->depthBuffer[y * 1000 + x] >= 250 ? 1 : zBuffer->depthBuffer[y * 1000 + x];

	//					int color = int(_color * 255);

	//					img.set_pixel(x, y, color, color, color);
	//				}
	//			}

	//			img.write("shadow.bmp");
	//		}



	//		//{

	//		//	BmpImg img(1000, 1000);

	//		//	for (int y = 0, x; y < 1000; y++)
	//		//	{
	//		//		for (x = 0; x < 1000; x++)
	//		//		{
	//		//			float _color = zBuffer->depthBuffer[y * 1000 + x] >= 250 ? 1 : zBuffer->depthBuffer[y * 1000 + x];

	//		//			int color = this->screenHDC;

	//		//			img.set_pixel(x, y, color, color, color);
	//		//		}
	//		//	}

	//		//	img.write("shadow.bmp");
	//		//}


	//	}



	//}

	//void Renderer::RasterizeTrangle(Vertex& v0, Vertex& v1, Vertex& v2, IShader* shader, DepthBuffer* zBuffer)
	//{
	//	//拷贝，以防止篡改mash中的顶点（mash中的顶点永远是模型空间）
	//	Vertex _v0 = v0, _v1 = v1, _v2 = v2;

	//	shader->VS(_v0, _v1, _v2);//以完成mvp(未标准化，矫正需要观察空间下的Z值)，并且完成了绘制上下三角形所需的排序//参数会同步改变


	//	//齐次除法的屏幕映射(未调整w)//但这一次Uniform不会同步
	//	PrepareRasterization(_v0, zBuffer);
	//	PrepareRasterization(_v1, zBuffer);
	//	PrepareRasterization(_v2, zBuffer);



	//	if (_v2.position.y == _v1.position.y) {

	//		DrawBottomTriangle(_v0, _v1, _v2, shader, zBuffer, _v2);

	//	}
	//	else if (_v0.position.y == _v1.position.y) {

	//		DrawTopTriangle(_v0, _v1, _v2, shader, zBuffer, _v0);

	//	}
	//	else {

	//		//MVP三个变换都是线性的，这导致关系（即比例）一定是固化的，即那个未齐次除法的中间结果一定也是固化的比例
	//		float m = (_v2.position.y - _v1.position.y) / (_v2.position.y - _v0.position.y);
	//		Vertex _v = Vertex::LerpVertex(_v2, _v0, m);//一个屏幕空间中的空间点，只有position中的xy是有意义的

	//		//很容易理解，在MV阶段，比例关系必然不变（因为空间变换总是线性的）
	//		//但P令我犹豫了，尽管它也是线性的，但是那个w带来了一些不必要的顾虑，因为两个点在某个轴投影上相同，或者保持比例，那么任何线性变换后，在该轴投影上的比例还是保持一致的
	//		//但是注意，是“轴”，空间在线性变换后，空间的基准轴往往就不再能够通过单个维度表达，而是多个维度，更像一个向量
	//		//简单来说，单个维度上的值的比例关系已经失真
	//		//而对每个向量的齐次除法从空间来看是一个非线性的变换
	//		//。。。

	//		DrawTopTriangle(_v0, _v1, _v2, shader, zBuffer, _v);
	//		DrawBottomTriangle(_v0, _v1, _v2, shader, zBuffer, _v);

	//	}



	//}

	////对参数同步改变
	//void Renderer::PrepareRasterization(Vertex& vertex, DepthBuffer* zBuffer)
	//{

	//	//促使位置向纹理Buffer的大小同步
	//	vertex.position.x = ((vertex.position.x / vertex.position.w) + 0.5) * (zBuffer->width - 1);
	//	vertex.position.y = ((vertex.position.y / vertex.position.w) + 0.5) * (zBuffer->height - 1);
	//	vertex.position.z = vertex.position.z / vertex.position.w;
	//	//w无需变化,留下有用

	//}

	//void Renderer::DrawTopTriangle(Vertex& v0, Vertex& v1, Vertex& v2, IShader* shader, DepthBuffer* zBuffer, Vertex& interpolateVertex)
	//{
	//	//流程是，确定像素覆盖情况，然后将直线两端对应的

	//	if (abs(v1.position.y - v2.position.y) < 1) {
	//		return;
	//	}

	//	for (int y = interpolateVertex.position.y + 0.5; y <= int(v2.position.y - 0.5); y++) {

	//		float n = (v2.position.y - y) / (v2.position.y - interpolateVertex.position.y);
	//		Vertex temVertex_1 = Vertex::LerpVertex(v2, v1, n);
	//		Vertex temVertex_2 = Vertex::LerpVertex(v2, interpolateVertex, n);
	//		//这些点的位置未经过矫正，只有xy是正确的


	//		DrawLine(temVertex_1, temVertex_2, shader, zBuffer, v0.position, v1.position, v2.position);

	//	}
	//}

	//void Renderer::DrawBottomTriangle(Vertex& v0, Vertex& v1, Vertex& v2, IShader* shader, DepthBuffer* zBuffer, Vertex& interpolateVertex)
	//{
	//	if (abs(v1.position.y - v0.position.y) < 1) {
	//		return;
	//	}

	//	for (int y = interpolateVertex.position.y - 0.5; y >= int(v0.position.y + 0.5); y--) {

	//		float n = (v0.position.y - y) / (v0.position.y - interpolateVertex.position.y);
	//		Vertex temVertex_1 = Vertex::LerpVertex(v0, v1, n);
	//		Vertex temVertex_2 = Vertex::LerpVertex(v0, interpolateVertex, n);
	//		//这些点的位置未经过矫正，只有xy是正确的


	//		DrawLine(temVertex_1, temVertex_2, shader, zBuffer, v0.position, v1.position, v2.position);

	//	}
	//}

	//void Renderer::DrawLine(Vertex& aimVertex_1, Vertex& aimVertex_2, IShader* shader, DepthBuffer* zBuffer, Vector3f& v0, Vector3f& v1, Vector3f& v2)
	//{
	//	Vertex leftVertex = (aimVertex_1.position.x > aimVertex_2.position.x) ? aimVertex_2 : aimVertex_1;
	//	Vertex rightVertex = (aimVertex_1.position.x > aimVertex_2.position.x) ? aimVertex_1 : aimVertex_2;

	//	leftVertex.position.x = int(leftVertex.position.x - 0.5);
	//	rightVertex.position.x = int(rightVertex.position.x + 0.5);
	//	//这条直线间就是可着色范围（包括端点），两者刚好对应两个在位图中的像素索引

	//	if (abs(leftVertex.position.x - rightVertex.position.x) < 1) {
	//		return;
	//	}

	//	for (int x = leftVertex.position.x; x <= rightVertex.position.x; x++) {
	//		Vertex rendererVertex;
	//		rendererVertex.position.x = x; rendererVertex.position.y = leftVertex.position.y + 0.001f;//做一点矫正，有时可能会出现一点误差，比如预期343变成了342.999969

	//		//抽象的来说，FS之前的插值结果就是未校正的比例（当然仅对透视）
	//		Vector3f interpolation = CenterOfGravity_Projector(v0, v1, v2, rendererVertex.position);

	//		//虽然FS中的Uniform还停留在MVP这个阶段，但没关系，因为质心坐标才是最重要的
	//		//!!!（待更改）要将FS置于外层使用才行
	//		if (shader->FS(rendererVertex, interpolation))
	//			//产生必要的插值信息与最终该像素的颜色结果，并且确定是否在某个光源的阴影纹理中可见（就我了解的FS，这里它明显承担了一部分三角形遍历和设置的工作)
	//		{
	//			float depth = (rendererVertex.position.z / rendererVertex.position.w) - 0.5f;//将Z调整到0与-1之间
	//			if (ZTestAndWrite(rendererVertex.position.x, rendererVertex.position.y, depth, zBuffer))//！！！我突然意识到一个事情，这里的zBuffer真的是用来确定遮挡关系的，但Shader中的那个确实光源的
	//			{
	//				bool B = dynamic_cast<PhongShader*>(shader);
	//				if (B) {//PhongShader才允许执行对位图设置像素的功能

	//					int pixelX = (rendererVertex.position.x / (zBuffer->width - 1)) * (this->deviceWidth - 1);
	//					int pixelY = (rendererVertex.position.y / (zBuffer->height - 1)) * (this->deviceHeight - 1);

	//					if (pixelX >= 0 && pixelX < this->deviceWidth && pixelY >= 0 && pixelY < this->deviceHeight) {
	//						DrawPixel(pixelX, pixelY, rendererVertex.color);//记得从纹理的屏幕坐标映射回设备屏幕坐标
	//					}

	//				}
	//			}
	//		}
	//	}
	//}

	//void Renderer::DrawPixel(int x, int y, Color color)
	//{
	//	SetPixel(screenHDC, x, y, RGB(255 * color.r, 255 * color.g, 255 * color.b));
	//}

	//bool Renderer::ZTestAndWrite(int x, int y, float depth, DepthBuffer* zbuffer)
	//{
	//	float sample = zbuffer->Sample(x, y);
	//	bool tem = zbuffer->Sample(x, y) < depth;

	//	if (tem) {
	//		int index = y * zbuffer->width + x;
	//		zbuffer->depthBuffer[index] = depth;
	//		return true;
	//	}

	//	return false;
	//}

	//void Renderer::Clear(DepthBuffer* buffer)
	//{
	//	for (int y = 0; y < buffer->height; y++) {
	//		for (int x = 0; x < buffer->width; x++) {
	//			buffer->depthBuffer[y * buffer->width + x] = -1;
	//		}
	//	}

	//}
}

namespace newRender {

	/// <summary>
	/// ndc到屏幕空间，基于buffer的屏幕空间
	/// </summary>
	void Render::ScreenWorld() {

		//转向屏幕空间[width, height, 2]
		Matrix tem;
		tem.matrix[0][0] = this->currentCamera->zBuffer->width / 2.0;	tem.matrix[0][3] = 0.5 * this->currentCamera->zBuffer->width;
		tem.matrix[1][1] = this->currentCamera->zBuffer->height / 2.0;	tem.matrix[1][3] = 0.5 * this->currentCamera->zBuffer->height;
		tem.matrix[2][3] = 1.0;


		for (Vector3f ndcPoint : this->renderDate.ndcPositions) {
			this->renderDate.screenPositions.push_back(tem * ndcPoint);
		}

	}


	/// <summary>
	/// 从下到上的扫描
	/// </summary>
	void Render::ScanTriangle() {

		//排序
		std::vector<Vector3f> trianglePositions;
		trianglePositions.reserve(3);

		for (Vector3f screenPosition : this->renderDate.screenPositions) {
			trianglePositions.emplace_back(screenPosition);
		}

		//冒泡
		if (trianglePositions[1].y < trianglePositions[2].y) {

			trianglePositions[2] = this->renderDate.screenPositions[1];
			trianglePositions[1] = this->renderDate.screenPositions[2];
		}

		if (trianglePositions[0].y < trianglePositions[1].y) {

			trianglePositions[0] = trianglePositions[1];
			trianglePositions[1] = this->renderDate.screenPositions[0];

		}

		if (trianglePositions[1].y < trianglePositions[2].y) {

			Vector3f tem = trianglePositions[1];
			trianglePositions[1] = trianglePositions[2];
			trianglePositions[2] = tem;
		}


		int AABB_xMin = this->renderDate.screenPositions[0].x < this->renderDate.screenPositions[1].x ? this->renderDate.screenPositions[0].x : this->renderDate.screenPositions[1].x;
		AABB_xMin = AABB_xMin < this->renderDate.screenPositions[2].x ? AABB_xMin : this->renderDate.screenPositions[2].x;

		int AABB_xMax = this->renderDate.screenPositions[0].x > this->renderDate.screenPositions[1].x ? this->renderDate.screenPositions[0].x : this->renderDate.screenPositions[1].x;
		AABB_xMax = AABB_xMax > this->renderDate.screenPositions[2].x ? AABB_xMax : this->renderDate.screenPositions[2].x;


		int AABB_S = int(trianglePositions[0].y - trianglePositions[2].y) * int(AABB_xMax - AABB_xMin);//判断包围盒子大小

		//开辟空间
		this->renderDate.fragMates.clear();
		this->renderDate.fragMates.reserve(AABB_S);

		//确定像素
		int yMax = trianglePositions[0].y, yMin = trianglePositions[2].y;
		int yBoundary = trianglePositions[1].y + 0.5;//分界与分界以下归下三角
		
		
		for (int y = yMin; y <= yBoundary; y++) {

			Vector3f fouce_1, fouce_2;

			if ((trianglePositions[0].y - trianglePositions[2].y) >= 0.0005) {
				fouce_1 = Vector3f::LerpVector3(trianglePositions[0], trianglePositions[2], (trianglePositions[0].y - y) / (trianglePositions[0].y - trianglePositions[2].y));
			}
			else {
				fouce_1 = trianglePositions[0];
			}

			if ((trianglePositions[1].y - trianglePositions[2].y) >= 0.0005) {
				fouce_2 = Vector3f::LerpVector3(trianglePositions[1], trianglePositions[2], (trianglePositions[1].y - y) / (trianglePositions[1].y - trianglePositions[2].y));
			}
			else {
				fouce_2 = trianglePositions[1];
			}

			int left, right;
			 
			if (fouce_1.x >= fouce_2.x) {
				left = fouce_2.x - 0.5;
				right = fouce_1.x + 0.5;
			}
			else {
				left = fouce_1.x - 0.5;
				right = fouce_2.x + 0.5;
			}

			for (int x = left; x <= right; x++)
				this->renderDate.fragMates.emplace_back(FragDate{ {}, {x, y}, {} });//产生片元数据（这时只有屏幕坐标）
		}

		for (int y = yBoundary + 1; y <= yMax; y++) {

			Vector3f fouce_1, fouce_2;

			if ((trianglePositions[0].y - trianglePositions[1].y) >= 0.0005) {
				fouce_1 = Vector3f::LerpVector3(trianglePositions[0], trianglePositions[1], (trianglePositions[0].y - y) / (trianglePositions[0].y - trianglePositions[1].y));
			}
			else {
				fouce_1 = trianglePositions[1];
			}

			if ((trianglePositions[0].y - trianglePositions[2].y) >= 0.0005) {
				fouce_2 = Vector3f::LerpVector3(trianglePositions[0], trianglePositions[2], (trianglePositions[0].y - y) / (trianglePositions[0].y - trianglePositions[2].y));
			}
			else {
				fouce_1 = trianglePositions[2];
			}


			int left, right;

			if (fouce_1.x >= fouce_2.x) {
				left = fouce_2.x - 0.5;
				right = fouce_1.x + 0.5;
			}
			else {
				left = fouce_1.x - 0.5;
				right = fouce_2.x + 0.5;
			}

			for (int x = left; x <= right; x++)
				this->renderDate.fragMates.emplace_back(FragDate{ {}, {x, y}, {} });//产生片元数据（这时只有屏幕坐标）

		}

	}

	
	void Render::Interpolation() {

		for (FragDate& aimFrag : this->renderDate.fragMates) {

			Vector3f interpolation = CenterOfGravityInterpolation(
				this->renderDate.screenPositions[0],
				this->renderDate.screenPositions[1], 
				this->renderDate.screenPositions[2], 
				{ float(aimFrag.screenPosition.x), float(aimFrag.screenPosition.y), 0});
 
			float alpha, bate, gamma;

			alpha = interpolation.x, bate = interpolation.y, gamma = interpolation.z;

			if (this->currentCamera->isPerspective) {
				float zCorrection = 1 / ((-interpolation.x / this->renderDate.mvPositions[0].z) + (-interpolation.y / this->renderDate.mvPositions[1].z) + (-interpolation.z / this->renderDate.mvPositions[2].z));

				alpha = -interpolation.x * zCorrection / this->renderDate.mvPositions[0].z;
				bate = -interpolation.y * zCorrection / this->renderDate.mvPositions[1].z;
				gamma = -interpolation.z * zCorrection / this->renderDate.mvPositions[2].z;

			}

			aimFrag.interpolations = {alpha, bate, gamma, 0};

			//mv坐标
			aimFrag.fragVertex.position = this->renderDate.mvPositions[0] * alpha + this->renderDate.mvPositions[1] * bate + this->renderDate.mvPositions[2] * gamma;
			//mv法线
			aimFrag.fragVertex.normal = this->renderDate.mvNormals[0] * alpha + this->renderDate.mvNormals[1] * bate + this->renderDate.mvNormals[2] * gamma;
			aimFrag.fragVertex.normal.Normalize();

			//uv
			aimFrag.fragVertex.uv = this->renderDate.aimVertexs[0].uv * alpha + this->renderDate.aimVertexs[1].uv * bate + this->renderDate.aimVertexs[2].uv * gamma;


		}

	}

	void Render::TriangleRasterization() {

		this->ScreenWorld();//转换到屏幕空间

		//光栅化
		this->ScanTriangle();

		//插值
		this->Interpolation();

	}


	void Render::TriangleTraversal() {

		for (Vector3f mvpPosition : this->renderDate.mvpPositions) {

			this->renderDate.ndcPositions.push_back(mvpPosition.Standardization());//得到一个[2*2*2]的空间

		}

		this->TriangleRasterization();
	}

	Camera* Render::SetCurrentCamera(Camera* aimCamera) {

		Camera* oldCamera = this->currentCamera;
		this->currentCamera = aimCamera;
		this->renderDate.shadowShader->currentCamera = this->currentCamera;
		this->renderDate.renderShader->currentCamera = this->currentCamera;

		return oldCamera;
	}

	void Render::RunPipeLine() {

		int lightIndex = 0;

		//处理光源，得到光源的深度纹理
		for (Light* currentLight : this->renderDate.lights) {

			this->SetCurrentCamera(currentLight);

			int meshIndex = 0;
			//逐模型
			for (Mesh* currentMesh : this->renderDate.aimObjs) {

				//逐三角面
				for (const Vector3i& trangleIndex : currentMesh->trangleIndexBuffer) {

					this->renderDate.aimVertexs.clear();
					this->renderDate.mvPositions.clear();
					this->renderDate.mvNormals.clear();
					this->renderDate.mvpPositions.clear();
					this->renderDate.ndcPositions.clear();
					this->renderDate.screenPositions.clear();

					
					this->renderDate.aimVertexs.push_back(currentMesh->vertexBuffer[trangleIndex.x]);
					this->renderDate.aimVertexs.push_back(currentMesh->vertexBuffer[trangleIndex.y]);
					this->renderDate.aimVertexs.push_back(currentMesh->vertexBuffer[trangleIndex.z]);
					

					this->renderDate.shadowShader->VertShader(meshIndex);

					this->TriangleTraversal();

					this->renderDate.shadowShader->FragShader(meshIndex);

				}

				meshIndex++;
			}

			{
				BmpImg img(512, 512);

				for (int y = 0, x; y < 512; y++)
				{
					for (x = 0; x < 512; x++)
					{
						Color _color = this->currentCamera->cBuffer->Sample(x, 511- y);

						img.set_pixel(x, y, _color.r, _color.g, _color.b);
					}
				}

				std::string name = std::string("shadow_") + std::to_string(lightIndex) + std::string(".bmp");

				img.write(name);
			}

			lightIndex++;
		}


		this->SetCurrentCamera(this->renderDate.mainCamera);

		int meshIndex = 0;

		for (Mesh* currentMesh : this->renderDate.aimObjs) {

			for (Vector3i& trangleIndex : currentMesh->trangleIndexBuffer) {

				this->renderDate.aimVertexs.clear();
				this->renderDate.mvPositions.clear();
				this->renderDate.mvNormals.clear();
				this->renderDate.mvpPositions.clear();
				this->renderDate.ndcPositions.clear();
				this->renderDate.screenPositions.clear();


				this->renderDate.aimVertexs.push_back(currentMesh->vertexBuffer[trangleIndex.x]);
				this->renderDate.aimVertexs.push_back(currentMesh->vertexBuffer[trangleIndex.y]);
				this->renderDate.aimVertexs.push_back(currentMesh->vertexBuffer[trangleIndex.z]);


				this->renderDate.renderShader->VertShader(meshIndex);

				this->TriangleTraversal();

				this->renderDate.renderShader->FragShader(meshIndex);
			}

			meshIndex++;

		}

		{
			BmpImg img(512, 512);

			for (int y = 0, x; y < 512; y++)
			{
				for (x = 0; x < 512; x++)
				{
					float z = this->currentCamera->zBuffer->Sample(x, 511 - y);

					Color temColor = Color::white * ((this->currentCamera->farPlane - (z - 0.1)) / (this->currentCamera->farPlane - this->currentCamera->nearPlane));
					img.set_pixel(x, y, temColor.r, temColor.g, temColor.b);
				}
			}

			img.write("z.bmp");
		}

		{
			BmpImg img(512, 512);

			for (int y = 0, x; y < 512; y++)
			{
				for (x = 0; x < 512; x++)
				{
					Color temColor = this->currentCamera->cBuffer->Sample(x, 511 - y);

					img.set_pixel(x, y, temColor.r, temColor.g, temColor.b);
				}
			}

			img.write("color.bmp");
		}



	}

	void Render::DrawPixel(int x, int y, Color color) {

		SetPixel(screenHDC, x, y, RGB(255 * color.r, 255 * color.g, 255 * color.b));

	}


}