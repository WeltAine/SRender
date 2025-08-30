#include "../../Header/Rendering Core/Renderer.h"
#include "../../Header/Math/MyMath.h"

#include <iostream>
#include "../../Header/Tool/libbmp.h"
#include "../../Header/Tool/Instrumentor.h"


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


		for (Vector3f& ndcPoint : this->renderDate.ndcPositions) {
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

	//插值与矫正
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

	/// <summary>
	/// 三角形光栅化
	/// </summary>
	void Render::TriangleRasterization() {

		PROFILE_FUNCTION(0, 0);

		this->ScreenWorld();//转换到屏幕空间

		//光栅化（产生片元像素位置）
		this->ScanTriangle();

		//插值（补充各个片元属性）
		this->Interpolation();

	}

	/// <summary>
	/// 三角形遍历
	/// </summary>
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

		PROFILE_FUNCTION(0, 0);

		int lightIndex = 0;

		//处理光源，得到光源的深度纹理
		for (Light* currentLight : this->renderDate.lights) {

			this->SetCurrentCamera(currentLight);
			//刷新缓存
			this->currentCamera->zBuffer->Buffer::ResetBuffer();
			this->currentCamera->cBuffer->Buffer::ResetBuffer();

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


			//光源深度纹理图像
			{
				//BmpImg img(512, 512);
				//for (int y = 0, x; y < 512; y++)
				//{
				//	for (x = 0; x < 512; x++)
				//	{
				//		Color _color = this->currentCamera->cBuffer->Sample(x, 511- y);
				//
				//		img.set_pixel(x, y, _color.r, _color.g, _color.b);
				//	}
				//}
				//std::string name = std::string("shadow_") + std::to_string(lightIndex) + std::string(".bmp");
				//img.write(name);
			}

			lightIndex++;
		}


		this->SetCurrentCamera(this->renderDate.mainCamera);
		//刷新缓存
		this->currentCamera->zBuffer->Buffer::ResetBuffer();
		this->currentCamera->cBuffer->Buffer::ResetBuffer();

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

		//主相机深度纹理
		{
			//BmpImg img(512, 512);
			//for (int y = 0, x; y < 512; y++)
			//{
			//	for (x = 0; x < 512; x++)
			//	{
			//		float z = this->currentCamera->zBuffer->Sample(x, 511 - y);
			//		Color temColor = Color::white * ((this->currentCamera->farPlane - (z - 0.1)) / (this->currentCamera->farPlane - this->currentCamera->nearPlane));
			//		img.set_pixel(x, y, temColor.r, temColor.g, temColor.b);
			//	}
			//}
			//img.write("z.bmp");
		}

		//最终图像
		{
			//BmpImg img(512, 512);
			//for (int y = 0, x; y < 512; y++)
			//{
			//	for (x = 0; x < 512; x++)
			//	{
			//		Color temColor = this->currentCamera->cBuffer->Sample(x, 511 - y);
			//		img.set_pixel(x, y, temColor.r, temColor.g, temColor.b);
			//	}
			//}
			//img.write("color.bmp");
		}

		for (int y = 0; y < this->renderDate.mainCamera->cBuffer->height; y++) {

			for (int x = 0; x < this->renderDate.mainCamera->cBuffer->width; x++) {

				DrawPixel(x, this->renderDate.mainCamera->cBuffer->height - y - 1, this->renderDate.mainCamera->cBuffer->Sample(x, y));
			}
		}

	}

	void Render::DrawPixel(int x, int y, Color color) {

		SetPixel(screenHDC, x, y, RGB(color.r, color.g, color.b));

	}


}