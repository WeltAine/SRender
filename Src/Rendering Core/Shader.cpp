#include "../../Header/Rendering Core/Shader.h"
#include "../../Header/Math/MyMath.h"
#include "../../Header/Tool/Instrumentor.h"


namespace newShader {

	void IShader::SetCamera(Camera* camera) {
		this->currentCamera = camera;
	}

	void ShadowShader::VertShader(int meshIndex) {

		PROFILE_FUNCTION(0, 0);

		for (Vertex aimVertex : this->uDate->aimVertexs) {

			this->currentCamera->v * (this->uDate->aimObjs[meshIndex]->transform.objectToWorld * aimVertex);//MV�仯
			this->uDate->mvPositions.push_back( aimVertex.position );
			this->uDate->mvNormals.push_back(aimVertex.normal);

			this->uDate->mvpPositions.push_back(this->currentCamera->p * aimVertex.position);//�����mvp

		}
	}

	void ShadowShader::FragShader(int meshIndex) {

		PROFILE_FUNCTION(0, 0);

		for (FragDate aimFrag : this->uDate->fragMates) {

			PROFILE_SCOPE("OneFrag", 0, 1);

			float z = this->currentCamera->zBuffer->Sample(aimFrag.screenPosition.x, aimFrag.screenPosition.y);

			if (z > ((- aimFrag.fragVertex.position.z) + 0.1)) {//�Ա�

				if(this->currentCamera->zBuffer)
					this->currentCamera->zBuffer->UpdateBuffer(aimFrag.screenPosition.x, aimFrag.screenPosition.y, (-aimFrag.fragVertex.position.z) + 0.1);

				if (this->currentCamera->cBuffer) {
					Color temColor = Color::white * ((this->currentCamera->farPlane + aimFrag.fragVertex.position.z) / (this->currentCamera->farPlane - this->currentCamera->nearPlane));

					this->currentCamera->cBuffer->UpdateBuffer(aimFrag.screenPosition.x, aimFrag.screenPosition.y, temColor);
				}
			}
		}
	}




	void PhongShader::VertShader(int meshIndex) {

		for (Vertex aimVertex : this->uDate->aimVertexs) {//�˴������ã�֮�����ǻ���Ҫ���ԭʼ���ݸɵ���������

			this->currentCamera->v * (this->uDate->aimObjs[meshIndex]->transform.objectToWorld * aimVertex);//MV�仯
			this->uDate->mvPositions.push_back(aimVertex.position);
			this->uDate->mvNormals.push_back(aimVertex.normal);

			this->uDate->mvpPositions.push_back(this->currentCamera->p * aimVertex.position);//�����mvp

		}



	}

	void PhongShader::Shading(int meshIndex, FragDate& aimFrag) {

		PROFILE_FUNCTION(0, 2);

		//������ɫ�������⣬�����䣬�߹�
		float ambient = 0.1f, diffuse = 0.0f, specular = 0.0f;

		//�����ƬԪ��ģ�Ϳռ��µ�λ��
		Vector3f objectPoint = (this->uDate->aimVertexs[0].position * aimFrag.interpolations.x)
				+ (this->uDate->aimVertexs[1].position * aimFrag.interpolations.y)
				+ (this->uDate->aimVertexs[2].position * aimFrag.interpolations.z);


		//Ŀǰ�ʹ���ƽ�й⣬������Ӱ���򲻽��и߹������������
		for (Light* lightSrc : this->uDate->lights) {

			std::string profile_name = lightSrc->isPerspective ? "PointLight" : "DirectionLight";
			PROFILE_SCOPE(profile_name.c_str(), 0, 3);

			{
				//��Ӱ����
				//����ƬԪ�ڹ�Դ�ӽ��µĿɼ���
				bool isShadow = this->Shadow(meshIndex, lightSrc, objectPoint);

				if (!isShadow) {

					PROFILE_SCOPE("isNotShadow", 0, 4);

					Vector3f lightPosition = this->currentCamera->v * lightSrc->transform.position;//����Դ�任�������MV�ռ���
					//Vector3f lightDirection = dynamic_cast<DirectionLight*>(lightSrc) ? 
					//	this->currentCamera->v * lightSrc->transform.zAxis : (aimFrag.fragVertex.position - lightSrc->transform.position).Normalized();
					Vector3f lightDirection = !lightSrc->isPerspective ?
						this->currentCamera->v * lightSrc->transform.zAxis : (aimFrag.fragVertex.position - lightSrc->transform.position).Normalized();

					//������
					diffuse = max(0, Vector3f::Dot(lightDirection * -1, aimFrag.fragVertex.normal)) * lightSrc->intensity + diffuse;

					//�߹�
					Vector3f helfVector = ((Vector3f() - aimFrag.fragVertex.position).Normalized() - lightDirection).Normalized();
					specular = std::pow(max(0, Vector3f::Dot(helfVector, aimFrag.fragVertex.normal)), 256) * lightSrc->intensity + specular;
				}
			}
		}

		aimFrag.fragVertex.color = this->uDate->aimTextures[meshIndex]->Sample(aimFrag.fragVertex.uv.x, aimFrag.fragVertex.uv.y);//��ȡ��ɫ

		aimFrag.fragVertex.color = aimFrag.fragVertex.color * min(ambient + diffuse, 1) + Color::white * min(specular, 1);

	}


	bool PhongShader::Shadow(int meshIndex, const Light* currentLight, const Vector3f& objectPoint) {

		PROFILE_FUNCTION(0, 4);

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

		PROFILE_FUNCTION(0, 0);

		for (FragDate& aimFrag : this->uDate->fragMates)
		{
			PROFILE_SCOPE("OneFrag", 0, 1);
			float z = this->currentCamera->zBuffer->Sample(aimFrag.screenPosition.x, aimFrag.screenPosition.y);

			if (z > ((-aimFrag.fragVertex.position.z) + 0.1)) {//�Աȣ�ZTest

				if (this->currentCamera->zBuffer)
					this->currentCamera->zBuffer->UpdateBuffer(aimFrag.screenPosition.x, aimFrag.screenPosition.y, (-aimFrag.fragVertex.position.z) + 0.1);


				this->Shading(meshIndex, aimFrag);//��ɫ

				if (this->currentCamera->cBuffer)
					this->currentCamera->cBuffer->UpdateBuffer(aimFrag.screenPosition.x, aimFrag.screenPosition.y, aimFrag.fragVertex.color);//��ɫ

			}
		}

	}


}