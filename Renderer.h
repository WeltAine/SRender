#pragma once

#include "Vertex.h"
#include "Light.h"
#include "Texture.h"
#include "Camera.h"
#include"Shader.h"
#include "Mesh.h"
#include "Buffer.h"
#include "libbmp.h"



namespace newRender {

	class Render {

	public:
		RenderDate& renderDate;
		Camera* currentCamera;
		HDC screenHDC;
		int deviceWidth, deviceHeight;

		Render(HDC inScreenHDC, int inDeviceWidth, int inDeviceHeight, RenderDate& inRenderDate)
			:screenHDC{ inScreenHDC }, deviceHeight{ inDeviceHeight }, deviceWidth{ inDeviceWidth }, renderDate{ inRenderDate } 
		{
			currentCamera = nullptr;

			this->renderDate.mainCamera->zBuffer->ResetBuffer(deviceWidth, deviceHeight);
			this->renderDate.mainCamera->cBuffer->ResetBuffer(deviceWidth, deviceHeight);			
		}


		void ScreenWorld();
		
		void ScanTriangle();

		void Interpolation();

		void TriangleRasterization();

		void TriangleTraversal();

		Camera* SetCurrentCamera(Camera* aimCamera);

		void RunPipeLine();

		void DrawPixel(int x, int y, Color color);


	};

}

