#pragma once


#include <vector>
#include "../Scene Entities/Light.h"
#include "../Scene Entities/Camera.h"
#include "../Math/Matrix.h"
#include "Texture.h"
#include "Buffer.h"
#include "Mesh.h"

namespace newShader{
	class IShader;
}

//核心功能是记录两个着色器需要用到和产生的数据


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




