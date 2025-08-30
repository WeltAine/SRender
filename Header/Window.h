#pragma once

#include <windows.h>

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

