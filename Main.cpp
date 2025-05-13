#include "Renderer.h"
#include "ObjFileReader.h"
#include "Window.h"
#include "Input.h"
#include "Tool.h"
#include <iostream>


static const int windowWidth = 500;
static const int windowHeight = 500;

Renderer* device = nullptr;

Camera* mainCamera = new Camera( Transform(Vector3f(0, 10, -10), Vector3f(), Vector3f(1, 1, 1)) );
Vector3f deltaCameraPosition, deltaCameraRotation, * cameraDirection = new Vector3f(0, 0, 1, 0);


Mesh* currentMesh = nullptr, * plane = nullptr;
ShadowShader* shadow = nullptr;
PhongShader* meshPhong = nullptr, * planePhong = nullptr;

//目前只能运行单光源
DepthBuffer* depthBuffer = new DepthBuffer(windowWidth * 2, windowHeight * 2);//阴影的zbuffer
DepthBuffer* zBuffer = new DepthBuffer(windowWidth, windowHeight);//相机的zbuffer


void UpdateInput();
void Update(Window* w);
void DoRender(Window* w);
void ShowFPS(Window* w);
void CreateCube();
void CreatePlane();



void main() {

	//窗口配置
	Window* w = new Window(windowWidth, windowHeight, "Test");

	//渲染管线配置
	device = new Renderer(w->screenHDC, windowWidth, windowHeight, mainCamera);

		//加载纹理纹理
	Texture* gezi = new Texture();
	gezi->LoadTexture("gezi.bmp");

	
		//创建shader
	meshPhong = new PhongShader(PhongVert(), PhongFrag(gezi, depthBuffer));
	
		//设置光源与相关参数
	DirectionLight light(Vector3f(0, 10, -10), Vector3f(0, -1, 1), 1);
	meshPhong->phongVertex.directionLights.push_back(light);
	meshPhong->phongVertex.lightV = mainCamera->LookAt(light.position, light.direction, Vector3f(0, 1, 0));
	meshPhong->phongVertex.lightP = mainCamera->Orthographic(-10, 10, 0, 120, 10, -10);

		//设置相机与相关参数
	meshPhong->phongVertex.camera = mainCamera;
	meshPhong->phongVertex.v = mainCamera->LookAt(mainCamera->transform.position, mainCamera->transform.zAxis, mainCamera->transform.yAxis);
	meshPhong->phongVertex.p = mainCamera->Perspective(60, 1, 1, 10);

		//设置物体参数
	//meshPhong->phongVertex.m = 


	//---------------------------------------------------------------------------------------------------

		//创建shader
	planePhong = new PhongShader(PhongVert(), PhongFrag(gezi, depthBuffer));

		//设置光源与相关参数
	planePhong->phongVertex.directionLights.push_back(light);
	planePhong->phongVertex.lightV = mainCamera->LookAt(light.position, light.direction, Vector3f(0, 1, 0));
	planePhong->phongVertex.lightP = mainCamera->Orthographic(-10, 10, 0, 120, 10, -10);

		//设置相机与相关参数
	planePhong->phongVertex.camera = mainCamera;
	planePhong->phongVertex.v = mainCamera->LookAt(mainCamera->transform.position, mainCamera->transform.zAxis, mainCamera->transform.yAxis);
	planePhong->phongVertex.p = mainCamera->Perspective(60, 1, 1, 10);


	//读取模型
	ReadObjFile("cube.obj", currentMesh);

	Update(w);
	//DoRender();
	system("pause");

}


void UpdateInput()
{

	//相机的位移
	if (IS_KEY_DOWN('A'))
	{
		deltaCameraPosition.x -= 0.01f;
	}
	if (IS_KEY_DOWN('D'))
	{
		deltaCameraPosition.x += 0.01f;
	}
	if (IS_KEY_DOWN('W'))
	{
		deltaCameraPosition.y += 0.01f;
	}
	if (IS_KEY_DOWN('S'))
	{
		deltaCameraPosition.y -= 0.01f;
	}
	mainCamera->transform.Translate(deltaCameraPosition);//移动


	//相机的旋转
	if (IS_KEY_DOWN('J'))
	{
		deltaCameraRotation.y -= 0.1f;
	}
	if (IS_KEY_DOWN('L'))
	{
		deltaCameraRotation.y += 0.1f;
	}
	if (IS_KEY_DOWN('I'))
	{
		deltaCameraRotation.x -= 0.1f;
	}
	if (IS_KEY_DOWN('K'))
	{
		deltaCameraRotation.x += 0.1f;
	}
	mainCamera->transform.Rotate(deltaCameraRotation);//旋转


	mainCamera->v = mainCamera->LookAt(mainCamera->transform.position, mainCamera->transform.zAxis, mainCamera->transform.yAxis);

	//重置相机的delta
	deltaCameraPosition.x = 0;
	deltaCameraPosition.y = 0;
	deltaCameraPosition.z = 0;

	deltaCameraRotation.x = 0;
	deltaCameraRotation.y = 0;
	deltaCameraRotation.z = 0;
}


//？晚点让AI看看吧
void Update(Window* w)
{

	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		UpdateInput();

		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			DoRender(w);
			ShowFPS(w);
		}
	}

}


void DoRender(Window* w)
{
	device->Clear(depthBuffer);
	device->Clear(zBuffer);
	device->DrawMesh(*currentMesh, shadow, depthBuffer);
	device->DrawMesh(*plane, shadow, depthBuffer);
	device->DrawMesh(*currentMesh, meshPhong, zBuffer);
	device->DrawMesh(*plane, planePhong, zBuffer);
	//！！一个Mesh配一个Shader，这样太浪费时间了，也不和逻辑，造成这个现象的原因在于Uniform中的部分信息仅适配某一个mesh，对shader重载（）试试实现切换

	//双缓冲//？交给AI
	BitBlt(w->hdc, 0, 0, windowWidth, windowHeight, w->screenHDC, 0, 0, SRCCOPY);
}


void ShowFPS(Window* w)
{
	static float  fps = 0;
	static int    frameCount = 0;
	static float  currentTime = 0.0f;
	static float  lastTime = 0.0f;

	frameCount++;
	currentTime = timeGetTime() * 0.001f;

	if (currentTime - lastTime > 1.0f)
	{
		fps = (float)frameCount / (currentTime - lastTime);
		lastTime = currentTime;
		frameCount = 0;
	}

	char strBuffer[20];
	sprintf_s(strBuffer, 20, "%0.3f", fps);
	std::wstring tem = StringToWideString(strBuffer);
	TextOut(w->hdc, 0, 0, tem.c_str(), 6);
}




