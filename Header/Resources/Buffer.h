#pragma once

#include "../Math/MyMath.h"
#include "Color.h"
//#include "Camera.h"
//Camera和buffe相互组合，所以.h中只写声明，不写头文件，方法写在cpp中（如果你的方法没有用到对方的具体方法或者字段那就无所谓）来避头文件免循环依赖

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

	virtual void ResetBuffer(int _width, int _height) {

		if (this->width == _width && this->height == _height) {
			return;
		}


		delete[] buffer;

		this->width = _width;
		this->height = _height;
		buffer = new T[width * height];

	}

	void ResetBuffer() {

		this->ResetBuffer(width, height);//���ﴥ����̬��̬

	}

	virtual ~Buffer() { delete buffer; }
};

/// <summary>
/// 深度buffer，存储的就是mv空间时的深度值
/// </summary>
struct DepthBuffer : Buffer<float> {

	Camera* aimCamera;

	DepthBuffer(int width = 512, int height = 512, Camera* aimCamera = nullptr);

	~DepthBuffer() {}


	/// <summary>
	/// 采样
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <returns></returns>
	float Sample(int x, int y) const override;

	void UpdateBuffer(int x, int y, float value) override;

	void ResetBuffer(int width, int height) override;

};

struct ColorBuffer : Buffer<Color> {
	
	Camera* aimCamera;

	ColorBuffer(int width = 512, int height = 512, Camera* aimCamera = nullptr);

	~ColorBuffer() {};

	Color Sample(int x, int y) const override;

	void UpdateBuffer(int x, int y, Color value) override;

	void ResetBuffer(int width, int height) override;

};