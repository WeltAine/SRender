#pragma once

//？这个文件夹暂时看不太懂

#include <vector>
#include "Light.h"
#include "Camera.h"
#include "Matrix.h"
#include "Texture.h"
#include "Buffer.h"
#include "Mesh.h"

namespace newShader{
	class IShader;
}

//核心功能是记录两个着色器需要用到和产生的数据
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

	~PhongFrag() {
	};

	Texture* texture;
	DepthBuffer* depthBuffer;//？阴影用的深度图，！在Renderer的ZTestAndWirte中对Buffer的使用和Shader的FS对Buffer的使用，更加深了我对这个看法的认同

};

struct ShadowVert {

	Matrix m;
	Matrix lightV, lightP;

};



//透视矫正所用的空间是在MV中的（目前的推演中，也表明必须在MV中，因为Z的比例是矫正比例的关键，P会产生平移，破坏比例），错误比例继续使用ndc或者屏幕都行

/// <summary>
/// 三角形遍历后产生的片元数据
/// </summary>
struct FragDate {
	Vertex fragVertex;//包含每个片元的MV空间下的position, normal, uv。normal处理光照，uv没什么会产生变化的原因
	Vector2i screenPosition;
	Vector3f interpolations;//插值比例
};

struct RenderDate {

	std::vector<Mesh*> aimObjs{};//要渲染的模型
	std::vector<Texture*> aimTextures;//模型所使用的纹理
	std::vector<Light*> lights{};//光源
	Camera* mainCamera;//里头包含颜色和深度缓存

	newShader::IShader* shadowShader, * renderShader;


	std::vector<Vertex> aimVertexs;
	std::vector<Vector3f> mvpPositions;//未齐次化
	std::vector<Vector3f> mvPositions;//世界空间顶点，光照处理时使用
	std::vector<Vector3f> mvNormals;
	std::vector<Vector3f> ndcPositions;
	std::vector<Vector3f> screenPositions;
	std::vector<FragDate> fragMates;//它和上头那个都有屏幕坐标，不过量级完全不同

};


//struct VertDate {
//	//in
//	Transform objTransfron;//提供M
//	Camera* observeCamera;//提供V和P
//	std::vector<Vertex> triangleVertexs;
//
//	//out
//	std::vector<Vector3f> mvpPositions;
//	std::vector<Vector3f> mvPositions;
//	std::vector<Vector3f> mvNormals;
//
//};


