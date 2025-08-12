#pragma once

#include "Color.h"
#include <string>
#include "Camera.h"
#include "Buffer.h"


class Texture {

public:
	
	int width, height;//纹理大小，但是实际访问时使用UV统一规范访问
	//Color textureData[1024][1024];//纹理信息（1024 * 1024是最大存储空间）
	ColorBuffer textureData;


	Texture(int width = 225, int height = 225) : width{ width }, height{ height }, textureData{ width, height, nullptr } {};
	~Texture() {};

	void LoadTexture(const std::string& path);
	Color Sample(float u, float v) const;

};