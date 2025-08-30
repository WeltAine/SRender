#include "../Header/Rendering Core/Renderer.h"
#include "../Header/Window.h"
#include "../Header/Input.h"
#include <iostream>
#include <mmsystem.h>

#include "../Header/Tool/ObjFileReader.h"
#include "../Header/Tool/Instrumentor.h"
#include "../Header/Tool/libbmp.h"
#include "../Header/Tool/Tool.h"


#pragma comment(lib, "winmm.lib")

static const int windowWidth = 512;
static const int windowHeight = 512;

Window* w = new Window(windowWidth, windowHeight, "Test");//����

//��������͹�Դ
Camera mainCamera{ {}, true, 1, 1, 50, 60 };
DirectionLight directLight{ { {}, false, 1, 1, 50, 168.6 }, 1 };
PointLight pointLight{ { {}, true, 1, 1, 50, 60 }, 1 };
//����ģ��
Mesh cube{};
Mesh plane{};


//��������
Texture gezi = Texture(225, 225);

//����Ҫ��Ⱦ��ģ�ͣ�ÿ��ģ�͵��������й�Դ���������
//RenderDate rDate{ {&cube, &plane}, {gezi, gezi}, {&directLight}, {&mainCamera}, {}, {}, {}, {}, {}, {}, {} };//ֱ�߹�
//RenderDate rDate{ {&cube, &plane}, {gezi, gezi}, {&pointLight}, {&mainCamera}, {}, {}, {}, {}, {}, {}, {} };//���Դ
RenderDate rDate{ {&cube, &plane}, {&gezi, &gezi}, {&pointLight, &directLight}, {&mainCamera}, {}, {}, {}, {}, {}, {}, {} };//���Դ
newRender::Render render{ w->screenHDC, windowWidth, windowHeight, rDate };

//����ָ��shadow����Ҫ��ȡ������
newShader::ShadowShader shadowShader{ &rDate };
newShader::PhongShader phongShader{ &rDate };


void Update(Window* w);

int main() {

	//��������
	ReadObjFile("cube.obj", &cube);
	ReadObjFile("Plane.obj", &plane);
	gezi.LoadTexture("gezi.bmp");

	//��������
	rDate.shadowShader = &shadowShader;
	rDate.renderShader = &phongShader;

	//��������͹�Դλ��
	mainCamera.UpdateCamera({ {-2, 2, -2}, {45, 45, 0}, {1, 1, 1} }, true, 1, 1, 10, 60);//͸��
	//mainCamera.UpdateCamera({ {-2, 2, -2}, {45, 45, 0}, {1, 1, 1} }, false, 1, 1, 10, 130);//����
	
	directLight.UpdateCamera({ {2, 2, -2}, {30, -45, 0}, {1, 1, 1} }, false, 1, 1, 10, 130);
	pointLight.UpdateCamera({ {2, 2, -2}, {45, -45, 0}, {1, 1, 1} }, true, 1, 1, 10, 60);
	  

	//Instrumentor::Get().BeginSession("Main");

	//render.RunPipeLine();
	Update(w);
	system("pause");

	//Instrumentor::Get().EndSession();


	delete w;
	//delete gezi;
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

	// ���ո���Ƿ���
	if (IS_KEY_DOWN(VK_SPACE))
	{
		PostQuitMessage(0); // �����˳���Ϣ
		return; // ֱ�ӷ��أ������������
	}


	//�����λ��
	if (IS_KEY_DOWN('A'))
	{
		deltaCameraPosition.x -= 0.05f;
	}
	if (IS_KEY_DOWN('D'))
	{
		deltaCameraPosition.x += 0.05f;
	}
	if (IS_KEY_DOWN('W'))
	{
		deltaCameraPosition.z += 0.05f;
	}
	if (IS_KEY_DOWN('S'))
	{
		deltaCameraPosition.z -= 0.05f;
	}
	if (IS_KEY_DOWN('Q'))
	{
		deltaCameraPosition.y += 0.05f;
	}
	if (IS_KEY_DOWN('E'))
	{
		deltaCameraPosition.y -= 0.05f;
	}

	deltaCameraPosition = render.renderDate.mainCamera->transform.xAxis * deltaCameraPosition.x 
		+ render.renderDate.mainCamera->transform.yAxis * deltaCameraPosition.y
		+ render.renderDate.mainCamera->transform.zAxis * deltaCameraPosition.z;
	render.renderDate.mainCamera->transform.Translate(deltaCameraPosition);//�ƶ�


	//�������ת
	if (IS_KEY_DOWN('J'))
	{
		deltaCameraRotation.y -= 0.5f;
	}
	if (IS_KEY_DOWN('L'))
	{
		deltaCameraRotation.y += 0.5f;
	}
	if (IS_KEY_DOWN('I'))
	{
		deltaCameraRotation.x -= 0.5f;
	}
	if (IS_KEY_DOWN('K'))
	{
		deltaCameraRotation.x += 0.5f;
	}
	render.renderDate.mainCamera->transform.Rotate(deltaCameraRotation);//��ת


	//���������delta
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
