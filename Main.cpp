#include "Renderer.h"
#include "ObjFileReader.h"
#include "Window.h"
#include "Input.h"
#include "Tool.h"
#include <iostream>
#include <mmsystem.h>

#include "libbmp.h"


#pragma comment(lib, "winmm.lib")

namespace oldMain {
	//static const int windowWidth = 500;
	//static const int windowHeight = 500;

	//Renderer* device = nullptr;

	//Camera* mainCamera = new Camera(Transform(Vector3f(0, 0, -10), Vector3f(), Vector3f(1, 1, 1)));
	//Vector3f deltaCameraPosition, deltaCameraRotation, * cameraDirection = new Vector3f(0, 0, 1, 0);


	//Mesh* currentMesh = nullptr, * plane = nullptr;
	//ShadowShader* shadow = nullptr;
	//PhongShader* meshPhong = nullptr, * planePhong = nullptr;

	////目前只能运行单光源
	//DepthBuffer* _depthBuffer = new DepthBuffer(windowWidth * 2, windowHeight * 2);//阴影的zbuffer
	//DepthBuffer* zBuffer = new DepthBuffer(windowWidth, windowHeight);//相机的zbuffer


	//void UpdateInput();
	//void Update(Window* w);
	//void DoRender(Window* w);
	//void ShowFPS(Window* w);
	//void CreateCube();
	//void CreatePlane();



	//void main() {

	//	//窗口配置
	//	Window* w = new Window(windowWidth, windowHeight, "Test");

	//	//渲染管线配置
	//	device = new Renderer(w->screenHDC, windowWidth, windowHeight, mainCamera);

	//	//加载纹理纹理
	//	Texture* gezi = new Texture();
	//	gezi->LoadTexture("gezi.bmp");

	//	//创建shader
	//	shadow = new ShadowShader();

	//	//创建shader
	//	meshPhong = new PhongShader(PhongVert(), PhongFrag(gezi, _depthBuffer));

	//	//设置光源与相关参数
	////DirectionLight light(Vector3f(0, 20, 0), Vector3f(0, -1, 0), 1);
	//	DirectionLight light(Vector3f(10, 10, 10), Vector3f(-1, -1, -1), 1);
	//	meshPhong->phongVertex.directionLights.push_back(light);
	//	//meshPhong->phongVertex.lightV = shadow->shadowVertex.lightV = mainCamera->LookAt(light.position, light.direction, Vector3f(0, 0, -1));
	//	meshPhong->phongVertex.lightV = shadow->shadowVertex.lightV = mainCamera->LookAt(light.position, light.direction, Vector3f(0, 1, 0));
	//	meshPhong->phongVertex.lightP = shadow->shadowVertex.lightP = mainCamera->Orthographic(-5, 5, 5, -5, 15, 22);

	//	//设置相机与相关参数
	//	meshPhong->phongVertex.camera = mainCamera;
	//	meshPhong->phongVertex.v = mainCamera->LookAt(mainCamera->transform.position, mainCamera->transform.zAxis, mainCamera->transform.yAxis);
	//	meshPhong->phongVertex.p = mainCamera->Perspective(60, 1, 5, 15);

	//	//设置物体参数
	////meshPhong->phongVertex.m = 


	////---------------------------------------------------------------------------------------------------

	//	//创建shader
	//	planePhong = new PhongShader(PhongVert(), PhongFrag(gezi, _depthBuffer));

	//	//设置光源与相关参数
	//	planePhong->phongVertex.directionLights.push_back(light);
	//	planePhong->phongVertex.lightV = mainCamera->LookAt(light.position, light.direction, Vector3f(0, 1, 0));
	//	planePhong->phongVertex.lightP = mainCamera->Orthographic(-10, 10, 10, -10, 10, 40);

	//	//设置相机与相关参数
	//	planePhong->phongVertex.camera = mainCamera;
	//	planePhong->phongVertex.v = mainCamera->LookAt(mainCamera->transform.position, mainCamera->transform.zAxis, mainCamera->transform.yAxis);
	//	planePhong->phongVertex.p = mainCamera->Perspective(60, 1, 1, 10);


	//	currentMesh = new Mesh();
	//	plane = new Mesh();
	//	//读取模型
	//	ReadObjFile("cube.obj", currentMesh);

	//	Update(w);
	//	//DoRender();
	//	system("pause");

	//	delete[] _depthBuffer;
	//	delete gezi;
	//	delete[] mainCamera;
	//	delete[] cameraDirection;
	//	delete currentMesh;
	//	delete plane;
	//	delete shadow;//这个析构是如何运行的
	//	delete meshPhong;
	//	delete zBuffer;
	//	delete w;

	//}


	//void UpdateInput()
	//{

	//	//相机的位移
	//	if (IS_KEY_DOWN('A'))
	//	{
	//		deltaCameraPosition.x -= 0.01f;
	//	}
	//	if (IS_KEY_DOWN('D'))
	//	{
	//		deltaCameraPosition.x += 0.01f;
	//	}
	//	if (IS_KEY_DOWN('W'))
	//	{
	//		deltaCameraPosition.y += 0.01f;
	//	}
	//	if (IS_KEY_DOWN('S'))
	//	{
	//		deltaCameraPosition.y -= 0.01f;
	//	}
	//	mainCamera->transform.Translate(deltaCameraPosition);//移动


	//	//相机的旋转
	//	if (IS_KEY_DOWN('J'))
	//	{
	//		deltaCameraRotation.y -= 0.1f;
	//	}
	//	if (IS_KEY_DOWN('L'))
	//	{
	//		deltaCameraRotation.y += 0.1f;
	//	}
	//	if (IS_KEY_DOWN('I'))
	//	{
	//		deltaCameraRotation.x -= 0.1f;
	//	}
	//	if (IS_KEY_DOWN('K'))
	//	{
	//		deltaCameraRotation.x += 0.1f;
	//	}
	//	mainCamera->transform.Rotate(deltaCameraRotation);//旋转


	//	mainCamera->v = mainCamera->LookAt(mainCamera->transform.position, mainCamera->transform.zAxis, mainCamera->transform.yAxis);

	//	//重置相机的delta
	//	deltaCameraPosition.x = 0;
	//	deltaCameraPosition.y = 0;
	//	deltaCameraPosition.z = 0;

	//	deltaCameraRotation.x = 0;
	//	deltaCameraRotation.y = 0;
	//	deltaCameraRotation.z = 0;
	//}


	////？晚点让AI看看吧
	//void Update(Window* w)
	//{

	//	MSG msg = { 0 };
	//	while (msg.message != WM_QUIT)
	//	{
	//		UpdateInput();

	//		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
	//		{
	//			TranslateMessage(&msg);
	//			DispatchMessage(&msg);
	//		}
	//		else
	//		{
	//			DoRender(w);
	//			ShowFPS(w);
	//		}
	//	}

	//}


	//void DoRender(Window* w)
	//{
	//	device->Clear(_depthBuffer);
	//	device->Clear(zBuffer);
	//	device->DrawMesh(*currentMesh, shadow, _depthBuffer);
	//	{

	//		BmpImg img(1000, 1000);

	//		for (int y = 0, x; y < 1000; y++)
	//		{
	//			for (x = 0; x < 1000; x++)
	//			{
	//				float _color = _depthBuffer->depthBuffer[y * 1000 + x] >= 250 ? 1 : _depthBuffer->depthBuffer[y * 1000 + x];

	//				int color = int(_color * 255);

	//				img.set_pixel(x, y, color, color, color);
	//			}
	//		}

	//		img.write("shadow.bmp");
	//	}

	//	//device->DrawMesh(*plane, shadow, depthBuffer);
	//	device->DrawMesh(*currentMesh, meshPhong, zBuffer);
	//	//device->DrawMesh(*plane, planePhong, zBuffer);
	//	//！！一个Mesh配一个Shader，这样太浪费时间了，也不和逻辑，造成这个现象的原因在于Uniform中的部分信息仅适配某一个mesh，对shader重载（）试试实现切换

	//	//双缓冲//？交给AI
	//	BitBlt(w->hdc, 0, 0, windowWidth, windowHeight, w->screenHDC, 0, 0, SRCCOPY);
	//}


	//void ShowFPS(Window* w)
	//{
	//	static float  fps = 0;
	//	static int    frameCount = 0;
	//	static float  currentTime = 0.0f;
	//	static float  lastTime = 0.0f;

	//	frameCount++;
	//	currentTime = timeGetTime() * 0.001f;

	//	if (currentTime - lastTime > 1.0f)
	//	{
	//		fps = (float)frameCount / (currentTime - lastTime);
	//		lastTime = currentTime;
	//		frameCount = 0;
	//	}

	//	char strBuffer[20];
	//	sprintf_s(strBuffer, 20, "%0.3f", fps);
	//	std::wstring tem = StringToWideString(strBuffer);
	//	TextOut(w->hdc, 0, 0, tem.c_str(), 6);
	//}
}




	static const int windowWidth = 512;
	static const int windowHeight = 512;

	Window* w = new Window(windowWidth, windowHeight, "Test");//窗口

	
	Camera mainCamera{ {}, true, 1, 1, 50, 60 };
	DirectionLight directLight{};

	Mesh cube{};
	//ReadObjFile("cube.obj", &cube);

	//纹理
	Texture* gezi = new Texture(225, 225);

	RenderDate rDate{ {&cube}, {gezi}, {&directLight}, {&mainCamera}, {}, {}, {}, {}, {}, {}, {} };
	//RenderDate rDate{ {&cube}, {gezi}, {}, {&mainCamera}, {}, {}, {}, {}, {}, {}, {} };
	newRender::Render render{ w->screenHDC, windowWidth, windowHeight, rDate };

	newShader::ShadowShader shadowShader{ &rDate };
	newShader::PhongShader phongShader{ &rDate };


	int main() {
		
		//加载数据
		ReadObjFile("cube.obj", &cube);
		gezi->LoadTexture("gezi.bmp");//记得delete啊

		//调整配置
		rDate.shadowShader = &shadowShader;
		rDate.renderShader = &phongShader;

		{
			BmpImg img(512, 512);
		
			for (int y = 0, x; y < 512; y++)
			{
				for (x = 0; x < 512; x++)
				{
					Color temColor = mainCamera.cBuffer->Sample(511 - x, 511 - y);
		
					img.set_pixel(x, y, temColor.r, temColor.g, temColor.b);
				}
			}
		
			img.write("CameraColorBuffer.bmp");
		}
		
		//调整位置
		//mainCamera.UpdateCamera({ {0, 0, -5}, {}, {1, 1, 1} }, true, 1, 3, 7, 60);
		mainCamera.UpdateCamera({ {-2, 2, -2}, {45, 45, 0}, {1, 1, 1} }, true, 1, 1, 10, 60);

		//directLight.UpdateCamera({ {0, 5, -5}, {45, 0, 0}, {1, 1, 1} }, false, 1, 1, 50, 168.6);
		//directLight.UpdateCamera({ {-3, 3, -3}, {45, 45, 0}, {1, 1, 1} }, false, 1, 1, 10, 130);
		//directLight.UpdateCamera({ {-2, 2, -2}, {45, 45, 0}, {1, 1, 1} }, false, 1, 1, 10, 130);
		directLight.UpdateCamera({ {2, 2, -2}, {45, -45, 0}, {1, 1, 1} }, false, 1, 1, 10, 130);
		//directLight.UpdateCamera({ {-1, 1, -1}, {45, 45, 0}, {1, 1, 1} }, false, 1, 1, 10, 130);



		render.RunPipeLine();

		std::cin.get();

		delete gezi;
		return 0;
	}
	




