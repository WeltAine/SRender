#include "Texture.h"
#include "MyMath.h"
#include "Tool.h"
#include <windows.h>

Texture::Texture()
{
	//?项目上配的是512，不明白，纹理信息都给到了1024 * 1024了，可能是制作人当时找的素材就是512 * 512的
	width = 1024;
	height = 1024;
}

Texture::~Texture()
{
}

void Texture::LoadTexture(const std::string& path)
{

	//Windows GDI,以后再详细了解吧
	
	//转换字符（配置中的参数要求宽字符）
	std::wstring wstrPath = StringToWideString(path);

	//配置位图
	HBITMAP bitmap = (HBITMAP)LoadImage(NULL, wstrPath.c_str(), IMAGE_BITMAP, width, height, LR_LOADFROMFILE);//原项目在项目属性中将字符集更改为宽字符类型，我们还是使用Union，但这个参数要求是一个宽字符类型，我们需要一些更改

	//配置设备上下文（这里使用内存设备
	HDC hdc = CreateCompatibleDC(NULL);

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
			Color c((float)r / 256, (float)g / 256, (float)b / 256, 1);
			//草，很好地解释了为什么色彩地设置值在0到256之间
			this->textureData[i][j] = c;
		}
	}

}

Color Texture::Sample(float u, float v) const
{
	u = Clamp(u, 0, 1.0);
	v = Clamp(v, 0, 1.0);

	return this->textureData[int(v * height)][int(u * width)];
}
