#pragma once

#include "MyMath.h"
#include "Color.h"
//#include "Camera.h"
//缓存和深度缓存的纹理

class Camera;

template<typename T>
struct Buffer {
	int width, height;
	T* buffer;

	Buffer(int width = 512, int height = 512) : width{ width }, height{ height }, buffer{new T[width * height]} {};

	virtual T Sample(int x, int y) const = 0;

	virtual void UpdateBuffer(int x, int y, T value) {

		if (x >= width || x < 0 || y >= height || y < 0) {
			return;
		}

		this->buffer[y * width + x] = value;

	}

	void ResetBuffer(int width, int height) {

		delete[] buffer;

		this->width = width;
		this->height = height;
		buffer = new T[width * height];

	}

	virtual ~Buffer() { delete buffer; }
};

/// <summary>
/// 深度值在就是实际情况
/// </summary>
struct DepthBuffer : Buffer<float> {

	Camera* aimCamera;

	DepthBuffer(int width = 512, int height = 512, Camera* aimCamera = nullptr);

	~DepthBuffer() {}


	/// <summary>
	/// 超出Buffer时返回相机远平面大小
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <returns></returns>
	float Sample(int x, int y) const override;

	void UpdateBuffer(int x, int y, float value) override;

	void ResetBuffer(int width, int height);
};

struct ColorBuffer : Buffer<Color> {
	
	Camera* aimCamera;

	ColorBuffer(int width = 512, int height = 512, Camera* aimCamera = nullptr);

	~ColorBuffer() {};

	Color Sample(int x, int y) const override;

	void UpdateBuffer(int x, int y, Color value) override;

	void ResetBuffer(int width, int height);


};