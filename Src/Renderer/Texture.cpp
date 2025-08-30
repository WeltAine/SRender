#include "../../Header/Resources/Texture.h"
#include "../../Header/Math/MyMath.h"
#include "../../Header/Tool/Tool.h"
#include <windows.h>


void Texture::LoadTexture(const std::string& path)
{
	
	//转换字符（配置中的参数要求宽字符）
	std::wstring wstrPath = StringToWideString(path);

	//配置位图
	HBITMAP bitmap = (HBITMAP)LoadImage(NULL, wstrPath.c_str(), IMAGE_BITMAP, width, height, LR_LOADFROMFILE);//原项目在项目属性中将字符集更改为宽字符类型，我们还是使用Union，但这个参数要求是一个宽字符类型，我们需要一些更改

	//配置设备上下文（这里使用内存设备
	HDC hdc = CreateCompatibleDC(NULL);

	SelectObject(hdc, bitmap);

	//不应该先遍历height 然后遍历width么
	//这里似乎有办法提高读取效率
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
