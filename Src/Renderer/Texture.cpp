#include "../../Header/Resources/Texture.h"
#include "../../Header/Math/MyMath.h"
#include "../../Header/Tool/Tool.h"
#include <windows.h>


void Texture::LoadTexture(const std::string& path)
{
	
	//ת���ַ��������еĲ���Ҫ����ַ���
	std::wstring wstrPath = StringToWideString(path);

	//����λͼ
	HBITMAP bitmap = (HBITMAP)LoadImage(NULL, wstrPath.c_str(), IMAGE_BITMAP, width, height, LR_LOADFROMFILE);//ԭ��Ŀ����Ŀ�����н��ַ�������Ϊ���ַ����ͣ����ǻ���ʹ��Union�����������Ҫ����һ�����ַ����ͣ�������ҪһЩ����

	//�����豸�����ģ�����ʹ���ڴ��豸
	HDC hdc = CreateCompatibleDC(NULL);

	SelectObject(hdc, bitmap);

	//��Ӧ���ȱ���height Ȼ�����widthô
	//�����ƺ��а취��߶�ȡЧ��
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			COLORREF color = GetPixel(hdc, i, j);
			int r = color % 256;
			int g = (color >> 8) % 256;
			int b = (color >> 16) % 256;
			int a = (color >> 24) % 256;
			Color c(r, g, b, a);
			this->textureData.UpdateBuffer(j, i, c);
		}
	}

}

Color Texture::Sample(float u, float v) const
{
	int x = Clamp(u * width, 0, height - 1.0);
	int y = Clamp(v * height, 0, width - 1.0);

	//int y = max(0, int(v * height) - 1);
	//int x = max(0, int(u * width) - 1);

	return this->textureData.Sample(x, y);
}
