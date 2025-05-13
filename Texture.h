#pragma once

#include "Color.h"
#include <string>


class Texture {

public:
	
	int width, height;//纹理大小，但是实际访问时使用UV统一规范访问
	Color textureData[1024][1024];//纹理信息（1024 * 1024是最大存储空间）

	Texture();
	~Texture();

	void LoadTexture(const std::string& path);
	Color Sample(float u, float v) const;

};