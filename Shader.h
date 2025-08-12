#pragma once

#include "Vertex.h"
#include "Vector.h"
#include "Uniform.h"
#include "Matrix.h"
#include "camera.h"

//struct RenderDate;

//这里开始我可能就得大幅魔改了，原项目的流程有点乱
//我大体推演了原项目的渲染流程，它是将三角分为上下两个三角，然后用直线渲染三角，这样的策略也是为什么在VS中要对顶点排序的原因
//其次，我是完全没找到原项目对mvp变换后的z矫正，倒是有对x和y的矫正，不过倒是有对直线中点的比例透视矫正（因为是画线来绘制，所以是这个公式和我以前推导的结果不一样，但本质是一样的）
namespace oldShader {
	//struct IShader {
	//	Vertex v0, v1, v2;


	//	virtual void VS(Vertex& v0, Vertex& v1, Vertex& v2) = 0;//一次处理一个三角面
	//	virtual bool FS(Vertex& vertex, Vector3f interpolation) = 0;//要处理的点和其所在三角面的插值

	//	virtual ~IShader() = default;

	//};

	////！与原项目相比将顶点自身的变量移出Uniform.h，移到这里
	//struct PhongShader : public IShader {

	//	PhongVert phongVertex;
	//	PhongFrag phongFragment;

	//	//正在处理的顶点
	//	//Vertex v0, v1, v2;
	//	Vector3f lightPoint0, lightPoint1, lightPoint2;//这里可以改用Vector3f


	//	PhongShader(const PhongVert& inPhongVertex, const PhongFrag& inPhongFragment)
	//		:phongVertex(inPhongVertex), phongFragment(inPhongFragment) {
	//	};
	//	~PhongShader() {};


	//	// 通过 IShader 继承
	//	void VS(Vertex& v0, Vertex& v1, Vertex& v2) override;
	//	bool FS(Vertex& vertex, Vector3f interpolation) override;
	//	int CalculateShadow(Vector3f pos_LightSpace, float bias);//通过depthBuffer来决定是否处在阴影中，在返回0，不在返回1
	//};


	//struct ShadowShader : public IShader {

	//	ShadowVert shadowVertex;

	//	//正在处理的顶点
	//	//Vertex v0, v1, v2;

	//	ShadowShader() {};
	//	~ShadowShader() {};

	//	// 通过 IShader 继承
	//	void VS(Vertex& v0, Vertex& v1, Vertex& v2) override;
	//	bool FS(Vertex& vertex, Vector3f interpolation) override;

	//};
}


namespace newShader {


	class IShader {

	public:
		RenderDate* uDate;
		Camera* currentCamera;

		IShader(RenderDate* rDate) : uDate{ rDate } { currentCamera = nullptr; };

		void SetCamera(Camera* camera);

		virtual void VertShader(int meshIndex) = 0;
		virtual void FragShader(int meshIndex) = 0;

	};

	class ShadowShader : public newShader::IShader {

	public:
		ShadowShader(RenderDate* rDate) : IShader(rDate) {};

		void VertShader(int meshIndex) override;
		void FragShader(int meshIndex) override;


	};

	class PhongShader : public newShader::IShader {

	public:
		PhongShader(RenderDate* rDate) : newShader::IShader{ rDate } {};

		void VertShader(int meshIndex) override;
		void FragShader(int meshIndex) override;

		void Shading(int meshIndex, Vertex& aimVertex);

	};
}



