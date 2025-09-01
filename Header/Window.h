#pragma once

#include <windows.h>
#include <cstdint>


namespace oldWindow {
	class Window
	{
	public:
		HWND window;
		int windowWidth;
		int windowHeight;
		HDC hdc;
		HDC screenHDC;
		Window(int w, int h, const char* name);
		~Window();

	};
}

class Window
{
public:
	HWND window;
	int windowWidth;
	int windowHeight;
	HDC hdc;
	HDC screenHDC;
	HBITMAP bitmapHandler; // 保存位图句柄
	uint32_t* frameBuffer; // 指向DIB段像素数据的指针

	Window(int w, int h, const char* name);
	~Window();
};
