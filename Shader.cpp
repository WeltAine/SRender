#include "Shader.h"
#include "MyMath.h"


namespace newShader {

	void IShader::SetCamera(Camera* camera) {
		this->currentCamera = camera;
	}

	void ShadowShader::VertShader(int meshIndex) {
		for (Vertex aimVertex : this->uDate->aimVertexs) {

			this->currentCamera->v * (this->uDate->aimObjs[meshIndex]->transform.objectToWorld * aimVertex);//MV变化
			this->uDate->mvPositions.push_back( aimVertex.position );
			this->uDate->mvNormals.push_back(aimVertex.normal);

			this->uDate->mvpPositions.push_back(this->currentCamera->p * aimVertex.position);//坐标的mvp

		}
	}

	void ShadowShader::FragShader(int meshIndex) {
		for (FragDate aimFrag : this->uDate->fragMates) {

			float z = this->currentCamera->zBuffer->Sample(aimFrag.screenPosition.x, aimFrag.screenPosition.y);

			if (z > ((- aimFrag.fragVertex.position.z) + 0.1)) {//对比

				if(this->currentCamera->zBuffer)
					this->currentCamera->zBuffer->UpdateBuffer(aimFrag.screenPosition.x, aimFrag.screenPosition.y, (-aimFrag.fragVertex.position.z) + 0.1);

				if (this->currentCamera->cBuffer) {
					Color temColor = Color::white * ((this->currentCamera->farPlane + aimFrag.fragVertex.position.z) / (this->currentCamera->farPlane - this->currentCamera->nearPlane));
					//temColor.a = 255;

					this->currentCamera->cBuffer->UpdateBuffer(aimFrag.screenPosition.x, aimFrag.screenPosition.y, temColor);
				}
			}
		}
	}




	void PhongShader::VertShader(int meshIndex) {

		for (Vertex aimVertex : this->uDate->aimVertexs) {//此处不引用，之后我们还需要这个原始数据干点其他事情

			this->currentCamera->v * (this->uDate->aimObjs[meshIndex]->transform.objectToWorld * aimVertex);//MV变化
			this->uDate->mvPositions.push_back(aimVertex.position);
			this->uDate->mvNormals.push_back(aimVertex.normal);

			this->uDate->mvpPositions.push_back(this->currentCamera->p * aimVertex.position);//坐标的mvp

		}



	}

	void PhongShader::Shading(int meshIndex, FragDate& aimFrag) {

		//计算颜色，环境光，漫反射，高光
		float ambient = 0.1f, diffuse = 0.0f, specular = 0.0f;

		//目前就处理平行光，处于阴影中则不进行高光与漫反射计算
		for (Light* lightSrc : this->uDate->lights) {

			//阴影处理
			Vector3f objectPoint = (this->uDate->aimVertexs[0].position * aimFrag.interpolations.x) + (this->uDate->aimVertexs[1].position * aimFrag.interpolations.y) + (this->uDate->aimVertexs[2].position * aimFrag.interpolations.z);

			bool isShadow = this->Shadow(meshIndex, lightSrc, objectPoint);

			if (!isShadow) {

				Vector3f lightPosition = this->currentCamera->v * lightSrc->transform.position;
				Vector3f lightDirection = this->currentCamera->v * lightSrc->transform.zAxis;//对于点光源更换一下这个变量的计算方式应该就可以了

				//漫反射
				diffuse = max(0, Vector3f::Dot(lightDirection * -1, aimFrag.fragVertex.normal)) * lightSrc->intensity + diffuse;

				//高光
				Vector3f helfVector = ((Vector3f() - aimFrag.fragVertex.position).Normalized() - lightDirection).Normalized();
				specular = std::pow(max(0, Vector3f::Dot(helfVector, aimFrag.fragVertex.normal)), 256) * lightSrc->intensity + specular;
			}
		}

		aimFrag.fragVertex.color = this->uDate->aimTextures[meshIndex]->Sample(aimFrag.fragVertex.uv.x, aimFrag.fragVertex.uv.y);//获取颜色

		aimFrag.fragVertex.color = aimFrag.fragVertex.color * min(ambient + diffuse, 1) + Color::white * min(specular, 1);

	}


	bool PhongShader::Shadow(int meshIndex, const Light* currentLight, const Vector3f& objectPoint) {

		Vector3f LightSpaceMV = currentLight->v * this->uDate->aimObjs[meshIndex]->transform.objectToWorld * objectPoint;
		
		Vector3f LightSpaceMVP = currentLight->p * LightSpaceMV;
		Vector3f LightSpaceNDC = LightSpaceMVP.Standardization();

		Matrix tem;
		tem.matrix[0][0] = currentLight->zBuffer->width / 2.0;	tem.matrix[0][3] = 0.5 * currentLight->zBuffer->width;
		tem.matrix[1][1] = currentLight->zBuffer->height / 2.0;	tem.matrix[1][3] = 0.5 * currentLight->zBuffer->height;
		tem.matrix[2][3] = 1.0;

		Vector3f LightSpaceScreen = tem * LightSpaceNDC;
		
		float z = currentLight->zBuffer->Sample(int(LightSpaceScreen.x), (LightSpaceScreen.y));

		return ( - LightSpaceMV.z) > z;

	}

	void PhongShader::FragShader(int meshIndex) {

		for (FragDate& aimFrag : this->uDate->fragMates) {

			float z = this->currentCamera->zBuffer->Sample(aimFrag.screenPosition.x, aimFrag.screenPosition.y);

			if (z > ((-aimFrag.fragVertex.position.z) + 0.1)) {//对比，ZTest

				if(this->currentCamera->zBuffer)
					this->currentCamera->zBuffer->UpdateBuffer(aimFrag.screenPosition.x, aimFrag.screenPosition.y, (-aimFrag.fragVertex.position.z) + 0.1);

				this->Shading(meshIndex, aimFrag);//着色

				if(this->currentCamera->cBuffer)
					this->currentCamera->cBuffer->UpdateBuffer(aimFrag.screenPosition.x, aimFrag.screenPosition.y, aimFrag.fragVertex.color);//填色

			}


		}

	}


}