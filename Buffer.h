#pragma once

#include "MyMath.h"

//缓存和深度缓存的纹理

struct Buffer {
	int width, height;
};

struct DepthBuffer : Buffer {

	float* depthBuffer;

	DepthBuffer(int width, int height) 
		: Buffer{width, height}
	{
		const int _width = width;
		depthBuffer = new float[width * height];

		for (int i = 0; i < width * height; i++) {
			depthBuffer[i] = 1;
		}

	}

	~DepthBuffer() {
		delete[] depthBuffer;
	}

	//深度缓冲采样
	float Sample(float x, float y) {

		if (x >= width || x < 0 || y >= height || y < 0) {
			return -10;
		}

		//像素中心坐标
		int _x = Clamp(x, 0, width - 1);
		int _y = Clamp(y, 0, height - 1);

		return this->depthBuffer[_y * width + _x];

	}
};