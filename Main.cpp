#include "Renderer.h"
#include "ObjFileReader.h"
#include "Window.h"
#include "Input.h"
#include "Tool.h"
#include <iostream>
#include <mmsystem.h>

#include "libbmp.h"


#pragma comment(lib, "winmm.lib")

static const int windowWidth = 512;
static const int windowHeight = 512;

Window* w = new Window(windowWidth, windowHeight, "Test");//窗口


Camera mainCamera{ {}, true, 1, 1, 50, 60 };
Camera dlCamera{ {}, false, 1, 1, 50, 168.6 };
DirectionLight directLight{ dlCamera, 1 };

Mesh cube{};
Mesh plane{};


//纹理
Texture* gezi = new Texture(225, 225);

RenderDate rDate{ {&cube, &plane}, {gezi, gezi}, {&directLight}, {&mainCamera}, {}, {}, {}, {}, {}, {}, {} };
newRender::Render render{ w->screenHDC, windowWidth, windowHeight, rDate };

newShader::ShadowShader shadowShader{ &rDate };
newShader::PhongShader phongShader{ &rDate };


void Update(Window* w);

int main() {

	//加载数据
	ReadObjFile("cube.obj", &cube);
	ReadObjFile("Plane.obj", &plane);
	gezi->LoadTexture("gezi.bmp");//记得delete啊

	//调整配置
	rDate.shadowShader = &shadowShader;
	rDate.renderShader = &phongShader;


	//调整位置
	//mainCamera.UpdateCamera({ {0, 0, -5}, {}, {1, 1, 1} }, true, 1, 3, 7, 60);
	mainCamera.UpdateCamera({ {-2, 2, -2}, {45, 45, 0}, {1, 1, 1} }, true, 1, 1, 10, 60);//这里在设置时用到的transform地址是DirectLight的aimCurrent地址

	//directLight.UpdateCamera({ {0, 5, -5}, {45, 0, 0}, {1, 1, 1} }, false, 1, 1, 50, 168.6);
	//directLight.UpdateCamera({ {-3, 3, -3}, {45, 45, 0}, {1, 1, 1} }, false, 1, 1, 10, 130);
	//directLight.UpdateCamera({ {-2, 2, -2}, {45, 45, 0}, {1, 1, 1} }, false, 1, 1, 10, 130);
	directLight.UpdateCamera({ {2, 2, -2}, {30, -45, 0}, {1, 1, 1} }, false, 1, 1, 10, 130);
	//directLight.UpdateCamera({ {-1, 1, -1}, {45, 45, 0}, {1, 1, 1} }, false, 1, 1, 10, 130);



	//render.RunPipeLine();
	Update(w);
	system("pause");

	

	delete gezi;
	return 0;
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

Vector3f deltaCameraPosition{};
Vector3f deltaCameraRotation{};

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
		deltaCameraPosition.z += 0.01f;
	}
	if (IS_KEY_DOWN('S'))
	{
		deltaCameraPosition.z -= 0.01f;
	}
	if (IS_KEY_DOWN('Q'))
	{
		deltaCameraPosition.y += 0.01f;
	}
	if (IS_KEY_DOWN('E'))
	{
		deltaCameraPosition.y -= 0.01f;
	}

	render.renderDate.mainCamera->transform.Translate(deltaCameraPosition);//移动


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
	render.renderDate.mainCamera->transform.Rotate(deltaCameraRotation);//旋转


	//重置相机的delta
	deltaCameraPosition.x = 0;
	deltaCameraPosition.y = 0;
	deltaCameraPosition.z = 0;

	deltaCameraRotation.x = 0;
	deltaCameraRotation.y = 0;
	deltaCameraRotation.z = 0;
}


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
			render.RunPipeLine();
			BitBlt(w->hdc, 0, 0, windowWidth, windowHeight, w->screenHDC, 0, 0, SRCCOPY);
			ShowFPS(w);
		}
	}

}
