#pragma once

#include "Vertex.h"
#include "Vector.h"
#include "Uniform.h"
#include "Matrix.h"
#include "camera.h"


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

		void Shading(int meshIndex, FragDate& aimFrag);

		bool Shadow(int meshIndex, const Light* currentLight, const Vector3f& objectPoint);

	};
}



