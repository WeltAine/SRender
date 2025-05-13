#pragma once

//？这个文件夹暂时看不太懂

#include <vector>
#include "Light.h"
#include "Camera.h"
#include "Matrix.h"
#include "Texture.h"
#include "Buffer.h"


struct PhongVert {

	std::vector<DirectionLight> directionLights;
	std::vector<PointLight> pointLights;

	Camera* camera;//包含vp变换

	Matrix m;//mesh的m变换，！！这个m应该交给mesh，而不是shader
	Matrix v, p;//基于相机的VP变换，！！相机自己有这个参数，之后尝试优化掉它

	Matrix lightV, lightP;
	
};


//？片元
struct PhongFrag {

	PhongFrag(Texture* inTexture, DepthBuffer* inDepthBuffer) 
		:texture(inTexture), depthBuffer(inDepthBuffer)
	{};

	~PhongFrag() {};

	Texture* texture;
	DepthBuffer* depthBuffer;//？阴影用的深度图，！在Renderer的ZTestAndWirte中对Buffer的使用和Shader的FS对Buffer的使用，更加深了我对这个看法的认同

};

struct ShadowVert {

	Matrix m;
	Matrix lightV, lightP;

};
