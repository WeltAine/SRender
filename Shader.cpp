#include "Shader.h"
#include "MyMath.h"


namespace old {
	////顶点变换，顶点颜色计算（带光照）
	//void PhongShader::VS(Vertex& v0, Vertex& v1, Vertex& v2)//对参数同步改变
	//{
	//	//M变换,同时改变位置和法线，并且将顶点信息计入到lP0~2中
	//	//法线只经历m变换，不经历VP，至于和视点夹角的计算一会会看到
	//	this->lightPoint0 = (this->phongVertex.m * v0).position;
	//	this->lightPoint1 = (this->phongVertex.m * v1).position;
	//	this->lightPoint2 = (this->phongVertex.m * v2).position;


	//	//各顶点处理
	//	Vertex* temVertex;
	//	for (int i = 1; i < 4; i++) {

	//		switch (i)
	//		{
	//		case(1):
	//			temVertex = &v0;
	//			break;

	//		case(2):
	//			temVertex = &v1;
	//			break;

	//		case(3):
	//			temVertex = &v2;
	//			break;

	//		default:
	//			temVertex = nullptr;
	//			break;
	//		}


	//		//计算颜色，环境光，漫反射，高光（也就是说这里我们采取的着色频率是顶点着色）
	//		float ambient = 0.1f, diffuse = 0.0f, specular = 0.0f;
	//		//漫反射
	//			//方向光
	//		for (auto light : this->phongVertex.directionLights) {
	//			diffuse = max(0, Vector3f::Dot(light.GetDirection(), temVertex->normal)) * light.intensity + diffuse;
	//		}
	//		//点光源
	//		for (auto light : this->phongVertex.pointLights) {
	//			Vector3f lightDirection = temVertex->position - light.position;
	//			float intensity = light.intensity / Vector3<float>::Dot(lightDirection, lightDirection);
	//			diffuse = max(0, Vector3f::Dot(lightDirection, temVertex->normal)) * intensity + diffuse;
	//		}

	//		//高光
	//		Vector3f viewDirection = (this->phongVertex.camera->transform.position - temVertex->position).Normalize();//从顶点到摄像头
	//		//方向光
	//		for (auto light : this->phongVertex.directionLights) {
	//			Vector3f halfVector = (light.GetDirection() + viewDirection).Normalize();
	//			specular = std::powf(max(0, Vector3f::Dot(halfVector, temVertex->normal)), 256) * light.intensity + specular;
	//		}
	//		//点光源
	//		for (auto light : this->phongVertex.pointLights) {
	//			Vector3f lightDirection = (temVertex->position - light.position).Normalize();
	//			float intensity = light.intensity / Vector3<float>::Dot(lightDirection, lightDirection);
	//			Vector3f halfVector = (lightDirection + viewDirection).Normalize();
	//			specular = std::powf(max(0, Vector3f::Dot(halfVector, temVertex->normal)), 128) * intensity + specular;
	//		}

	//		//设置颜色
	//		temVertex->color = temVertex->color * min(ambient + diffuse, 1) + Color::white * min(specular, 1);

	//		//VP变换
	//		temVertex->position = this->phongVertex.p * this->phongVertex.v * temVertex->position;
	//		//标准化处理（解决Z倍扩增）
	//		//！！或许我们还是不能在这个阶段就做齐次处理，矫正需要的是观察空间中的顶点Z坐标，对着MVP齐次除法化后的顶点是锁在正方体中的，此时的本质和正交投影一致，比例是无需矫正
	//		//temVertex->position.Standardization();

	//		//向VS和FS之间的Uniform同步顶点的MVP变换结果
	//		switch (i)
	//		{
	//		case(1):
	//			this->v0 = *temVertex;
	//			break;

	//		case(2):
	//			this->v1 = *temVertex;
	//			break;

	//		case(3):
	//			this->v2 = *temVertex;
	//			break;

	//		default:
	//			temVertex = nullptr;
	//			break;
	//		}
	//	}

	//	//光源视角结果？但是，是不是不够阿，我们可能有多个光源，￥留着以后改进吧
	//	this->lightPoint0 = this->phongVertex.lightP * (this->phongVertex.lightV * this->lightPoint0);
	//	this->lightPoint1 = this->phongVertex.lightP * (this->phongVertex.lightV * this->lightPoint1);
	//	this->lightPoint2 = this->phongVertex.lightP * (this->phongVertex.lightV * this->lightPoint2);
	//	//this->lightPoint0.Standardization();
	//	//this->lightPoint1.Standardization();
	//	//this->lightPoint2.Standardization();

	//	//最终从低到高是v0，v1, v2
	//	if ((v0.position.y / v0.position.w) > (v1.position.y / v1.position.w)) {
	//		std::swap(v0, v1);
	//		std::swap(this->v0, this->v1);
	//		std::swap(this->lightPoint0, this->lightPoint1);
	//	}
	//	if ((v1.position.y / v1.position.w) > (v2.position.y / v2.position.w)) {
	//		std::swap(v1, v2);
	//		std::swap(this->v1, this->v2);
	//		std::swap(this->lightPoint1, this->lightPoint2);
	//	}
	//	if ((v0.position.y / v0.position.w) > (v1.position.y / v1.position.w)) {
	//		std::swap(v0, v1);
	//		std::swap(this->v0, this->v1);
	//		std::swap(this->lightPoint0, this->lightPoint1);
	//	}

	//}


	////和我所知的
	//bool PhongShader::FS(Vertex& vertex, Vector3f interpolation)//这里的vertex应当是
	//{
	//	//！在原项目中参数vertex只有xyz， uv信息是有效的，其它信息都未经过插值的。这里我们只有xy是正常的，传过来的vertex是屏幕空间下的，并非NCP空间 
	//	float alpha = interpolation.x / v0.position.w;
	//	float beta = interpolation.y / v1.position.w;
	//	float gamma = interpolation.z / v2.position.w;

	//	//透视矫正,正交也不会有影响
	//	vertex.position.w = 1 / (alpha + beta + gamma);
	//	//mvp后的z，大小关系不会丢失
	//	vertex.position.z = (this->v0.position.z * alpha + this->v1.position.z * beta + this->v2.position.z * gamma) * vertex.position.w;

	//	//颜色插值
	//	vertex.uv = (v0.uv * alpha + v1.uv * beta + v2.uv * gamma) * vertex.position.w;
	//	vertex.color = (v0.color * alpha + v1.color * beta + v2.color * gamma) * vertex.position.w;
	//	vertex.color = vertex.color * this->phongFragment.texture->Sample(vertex.uv.x, vertex.uv.y);//纹理采样

	//	//法线插值
	//	vertex.normal = (v0.normal * alpha + v1.normal * beta + v2.normal * gamma) * vertex.position.w;

	//	//灯光投影视角位置插值，查到该点在光源空间下的坐标
	//	Vector3f posInLightSpace = (lightPoint0 * alpha + lightPoint1 * beta + lightPoint2 * gamma) * vertex.position.w;//用于访问shaderMap（就是那个depthBuffer）
	//	posInLightSpace.w = (lightPoint0.w * alpha + lightPoint1.w * beta + lightPoint2.w * gamma) * vertex.position.w;
	//	//l0~l2本来就只经历的mvp变换，来到了1 * 1 * 1
	//	//posInLightSpace.x /= posInLightSpace.w;
	//	//posInLightSpace.y /= posInLightSpace.w;

	//	//阴影偏差（这里只处理了直线光，而且目前的结构还只支持一个shadowmap）
	//	bool isDepth = 0;
	//	for (auto light : this->phongVertex.directionLights) {

	//		float bias = max(0.005, 0.02 * (1.0f - abs(Vector3f::Dot(vertex.normal, light.GetDirection()))));
	//		isDepth = CalculateShadow(posInLightSpace, bias) || isDepth;

	//	}

	//	vertex.color = vertex.color * isDepth;

	//	return isDepth;
	//}

	//int PhongShader::CalculateShadow(Vector3f posInLightSpace, float bias)
	//{
	//	//这里暂时也只支持直线光

	//	//屏幕坐标，
	//	Vector2f mapPos;
	//	mapPos.x = (posInLightSpace.x + 0.5f) * (this->phongFragment.depthBuffer->width - 1);
	//	mapPos.y = (posInLightSpace.y + 0.5f) * (this->phongFragment.depthBuffer->width - 1);

	//	float depth = posInLightSpace.w - 0.5f;

	//	//对比depth，如果可被看到， 那就返回1，否则0
	//	int shadow = ((depth - bias) < this->phongFragment.depthBuffer->Sample(mapPos.x, mapPos.y)) ? 0 : 1;

	//	return shadow;
	//}



	////感觉好像就没有用上，先不写
	//void ShadowShader::VS(Vertex& v0, Vertex& v1, Vertex& v2)
	//{
	//	Vertex* temVertex;

	//	for (int i = 0; i < 3; i++) {

	//		switch (i) {

	//		case(0): {
	//			temVertex = &v0;
	//			break;
	//		}

	//		case(1): {
	//			temVertex = &v1;
	//			break;
	//		}

	//		case(2): {
	//			temVertex = &v2;
	//			break;
	//		}
	//		default: {
	//			temVertex = nullptr;
	//			break;
	//		}

	//		}

	//		if (temVertex != nullptr)
	//			//M变换
	//			this->shadowVertex.m* (*temVertex);
	//		//VP变换
	//		temVertex->position = this->shadowVertex.lightP * (this->shadowVertex.lightV * temVertex->position);


	//		switch (i) {

	//		case(0): {
	//			this->v0 = *temVertex;
	//			break;
	//		}

	//		case(1): {
	//			this->v1 = *temVertex;
	//			break;
	//		}

	//		case(2): {
	//			this->v2 = *temVertex;
	//			break;
	//		}
	//		default: {
	//			break;
	//		}

	//		}


	//	}


	//	if (v0.position.y > v1.position.y) {
	//		std::swap(v0, v1);
	//		std::swap(this->v0, this->v1);
	//	}
	//	if (v1.position.y > v2.position.y) {
	//		std::swap(v1, v2);
	//		std::swap(this->v1, this->v2);
	//	}
	//	if (v0.position.y > v1.position.y) {
	//		std::swap(v0, v1);
	//		std::swap(this->v0, this->v1);
	//	}


	//}

	//bool ShadowShader::FS(Vertex& vertex, Vector3f interpolation)
	//{
	//	//！在原项目中参数vertex只有xyz， uv信息是有效的，其它信息都未经过插值的。这里我们只有xy是正常的，传过来的vertex是屏幕空间下的，并非NCP空间 
	//	float alpha = interpolation.x / v0.position.w;
	//	float beta = interpolation.y / v1.position.w;
	//	float gamma = interpolation.z / v2.position.w;

	//	vertex.position.w = 1 / (alpha + beta + gamma);
	//	//透视矫正//为mvp下的值
	//	vertex.position.z = (alpha * v0.position.z + beta * v1.position.z + gamma * v2.position.z) * vertex.position.w;
	//	//vertex.position.z = (this->v0.position.z * alpha + this->v1.position.z * beta + this->v2.position.z * gamma) * vertex.position.z;

	//	return true;//保证之后走到ZTest那里
	//}
}

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

	void PhongShader::Shading(int meshIndex, Vertex& aimVertex) {

		//计算颜色，环境光，漫反射，高光
		float ambient = 0.1f, diffuse = 0.0f, specular = 0.0f;

		//目前就处理平行光
		for (Light* lightSrc : this->uDate->lights) {
			Vector3f lightPosition = this->currentCamera->v * lightSrc->transform.position;
			Vector3f lightDirection = this->currentCamera->v * lightSrc->transform.zAxis;

			//漫反射
			diffuse = max(0, Vector3f::Dot(lightDirection * -1, aimVertex.normal)) * lightSrc->intensity + diffuse;

			//高光
			Vector3f helfVector = ((Vector3f() - aimVertex.position).Normalized() - lightDirection).Normalized();
			specular = std::pow(max(0, Vector3f::Dot(helfVector, aimVertex.normal)), 256) * lightSrc->intensity + specular;
		}

		aimVertex.color = this->uDate->aimTextures[meshIndex]->Sample(aimVertex.uv.x, aimVertex.uv.y);//获取颜色

		aimVertex.color = aimVertex.color * min(ambient + diffuse, 1) + Color::white * min(specular, 1);

	}

	void PhongShader::FragShader(int meshIndex) {

		for (FragDate& aimFrag : this->uDate->fragMates) {

			float z = this->currentCamera->zBuffer->Sample(aimFrag.screenPosition.x, aimFrag.screenPosition.y);

			if (z > ((-aimFrag.fragVertex.position.z) + 0.1)) {//对比，ZTest

				if(this->currentCamera->zBuffer)
					this->currentCamera->zBuffer->UpdateBuffer(aimFrag.screenPosition.x, aimFrag.screenPosition.y, (-aimFrag.fragVertex.position.z) + 0.1);

				this->Shading(meshIndex, aimFrag.fragVertex);//着色

				if(this->currentCamera->cBuffer)
					this->currentCamera->cBuffer->UpdateBuffer(aimFrag.screenPosition.x, aimFrag.screenPosition.y, aimFrag.fragVertex.color);//填色

			}


		}

	}


}