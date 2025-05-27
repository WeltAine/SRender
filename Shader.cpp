#include "Shader.h"
#include "MyMath.h"


//顶点变换，顶点颜色计算（带光照）
void PhongShader::VS(Vertex& v0, Vertex& v1, Vertex& v2)//对参数同步改变
{
	//M变换,同时改变位置和法线，并且将顶点信息计入到lP0~2中
	this->lightPoint0 = (this->phongVertex.m * v0).position;
	this->lightPoint1 = (this->phongVertex.m * v1).position;
	this->lightPoint2 = (this->phongVertex.m * v2).position;
	

	//各顶点处理
	Vertex* temVertex;
	for (int i = 1; i < 4; i++) {

		switch (i)
		{
		case(1):
			temVertex = &v0;
			break;

		case(2):
			temVertex = &v1;
			break;

		case(3):
			temVertex = &v2;
			break;

		default:
			temVertex = nullptr;
			break;
		}


		//计算颜色，环境光，漫反射，高光（也就是说这里我们采取的着色频率是顶点着色）
		float ambient = 0.1f, diffuse = 0.0f, specular = 0.0f;
		//漫反射
			//方向光
		for (auto light : this->phongVertex.directionLights) {
			diffuse = max(0, Vector3f::Dot(light.GetDirection(), temVertex->normal)) * light.intensity + diffuse;
		}
			//点光源
		for (auto light : this->phongVertex.pointLights) {
			Vector3f lightDirection = temVertex->position - light.position;
			float intensity = light.intensity / Vector3<float>::Dot(lightDirection, lightDirection);
			diffuse = max(0, Vector3f::Dot(lightDirection, temVertex->normal)) * intensity + diffuse;
		}

		//高光
		Vector3f viewDirection = (this->phongVertex.camera->transform.position - temVertex->position).Normalize();//从顶点到摄像头
			//方向光
		for (auto light : this->phongVertex.directionLights) {
			Vector3f halfVector = (light.GetDirection() + viewDirection).Normalize();
			specular = std::powf(max(0, Vector3f::Dot(halfVector, temVertex->normal)), 256) * light.intensity + specular;
		}
			//点光源
		for (auto light : this->phongVertex.pointLights) {
			Vector3f lightDirection = (temVertex->position - light.position).Normalize();
			float intensity = light.intensity / Vector3<float>::Dot(lightDirection, lightDirection);
			Vector3f halfVector = (lightDirection + viewDirection).Normalize();
			specular = std::powf(max(0, Vector3f::Dot(halfVector, temVertex->normal)), 128) * intensity + specular;
		}

		//设置颜色
		temVertex->color = temVertex->color * min(ambient + diffuse, 1) + Color::white * min(specular, 1);

		//VP变换
		temVertex->position = this->phongVertex.p * this->phongVertex.v * temVertex->position;
		//标准化处理（解决Z倍扩增）
		temVertex->position.Standardization();

		//向VS和FS之间的Uniform同步顶点的MVP变换结果
		switch (i)
		{
		case(1):
			this->v0 = *temVertex;
			break;

		case(2):
			this->v1 = *temVertex;
			break;

		case(3):
			this->v2 = *temVertex;
			break;

		default:
			temVertex = nullptr;
			break;
		}
	}

	//光源视角结果？但是，是不是不够阿，我们可能有多个光源，￥留着以后改进吧
	this->lightPoint0 = this->phongVertex.lightP * (this->phongVertex.lightV * this->lightPoint0);
	this->lightPoint1 = this->phongVertex.lightP * (this->phongVertex.lightV * this->lightPoint1);
	this->lightPoint2 = this->phongVertex.lightP * (this->phongVertex.lightV * this->lightPoint2);
	this->lightPoint0.Standardization();
	this->lightPoint1.Standardization();
	this->lightPoint2.Standardization();

	if (v0.position.y > v1.position.y) {
		std::swap(v0, v1);
		std::swap(this->v0, this->v1);
		std::swap(this->lightPoint0, this->lightPoint1);
	}
	if (v1.position.y > v2.position.y) {
		std::swap(v1, v2);
		std::swap(this->v1, this->v2);
		std::swap(this->lightPoint1, this->lightPoint2);
	}
	if (v0.position.y > v1.position.y) {
		std::swap(v0, v1);
		std::swap(this->v0, this->v1);
		std::swap(this->lightPoint0, this->lightPoint1);
	}

}


//和我所知的
bool PhongShader::FS(Vertex& vertex, Vector3f interpolation)//这里的vertex应当是
{
	//！在原项目中参数vertex只有xyz， uv信息是有效的，其它信息都未经过插值的。这里我们只有xy是正常的，传过来的vertex是屏幕空间下的，并非NCP空间 
	float alpha = interpolation.x / v0.position.z;
	float beta = interpolation.y / v1.position.z;
	float gamma = interpolation.z / v2.position.z;

	//透视矫正
	vertex.position.z = 1 / (alpha + beta + gamma);

	//颜色插值
	vertex.uv = (v0.uv * alpha + v1.uv * beta + v2.uv * gamma) * vertex.position.z;
	vertex.color = (v0.color * alpha + v1.color * beta + v2.color * gamma) * vertex.position.z;
	vertex.color = vertex.color * this->phongFragment.texture->Sample(vertex.uv.x, vertex.uv.y);//纹理采样

	//法线插值
	vertex.normal = (v0.normal * alpha + v1.normal * beta + v2.normal * gamma) * vertex.position.z;

	//灯光投影视角位置插值
	Vector3f posInLightSpace = (lightPoint0 * alpha + lightPoint1 * beta + lightPoint2 * gamma) * vertex.position.z;//用于访问shaderMap（就是那个depthBuffer）

	//阴影偏差（这里只处理了直线光，而且目前的结构还只支持一个shadowmap）
	bool isDepth = 0;
	for (auto light : this->phongVertex.directionLights) {

		float bias = max(0.005, 0.02 * (1.0f - abs(Vector3f::Dot(vertex.normal, light.GetDirection()))));
		isDepth = CalculateShadow(posInLightSpace, bias) || isDepth;

	}
	
	vertex.color = vertex.color * isDepth;

	return isDepth;
}

int PhongShader::CalculateShadow(Vector3f posInLightSpace, float bias)
{
	//屏幕坐标，
	Vector2f mapPos;
	mapPos.x = ((posInLightSpace.x + 1.0f) / 2) * (this->phongFragment.depthBuffer->width - 1);
	mapPos.y = ((posInLightSpace.y + 1.0f) / 2) * (this->phongFragment.depthBuffer->width - 1);

	float depth = (posInLightSpace.z + 1.0f) / 2;

	//对比depth，如果可被看到， 那就返回1，否则0
	int shadow = ((depth - bias) < this->phongFragment.depthBuffer->Sample(mapPos.x, mapPos.y)) ? 1 : 0;

	return shadow;
}



//感觉好像就没有用上，先不写
void ShadowShader::VS(Vertex& v0, Vertex& v1, Vertex& v2)
{
	Vertex* temVertex;

	for (int i = 0; i < 3; i++) {
		
		switch (i) {
			
		case(0): {
			temVertex = &v0;
			break;
		}

		case(1): {
			temVertex = &v1;
			break;
		}

		case(2): {
			temVertex = &v2;
			break;
		}
		default: {
			temVertex = nullptr;
			break;
		}

		}

		if(temVertex != nullptr)
		//MVP变换
		this->shadowVertex.lightP * (this->shadowVertex.lightV * (this->shadowVertex.m * (*temVertex)));


		switch (i) {

		case(0): {
			v0 = *temVertex;
			break;
		}

		case(1): {
			v1 = *temVertex;
			break;
		}

		case(2): {
			v2 = *temVertex;
			break;
		}
		default: {
			break;
		}

		}


	}


	if (v0.position.y > v1.position.y) {
		std::swap(v0, v1);
		std::swap(this->v0, this->v1);
	}
	if (v1.position.y > v2.position.y) {
		std::swap(v1, v2);
		std::swap(this->v1, this->v2);
	}
	if (v0.position.y > v1.position.y) {
		std::swap(v0, v1);
		std::swap(this->v0, this->v1);
	}


}

bool ShadowShader::FS(Vertex& vertex, Vector3f interpolation)
{
	//！在原项目中参数vertex只有xyz， uv信息是有效的，其它信息都未经过插值的。这里我们只有xy是正常的，传过来的vertex是屏幕空间下的，并非NCP空间 
	float alpha = interpolation.x / v0.position.z;
	float beta = interpolation.y / v1.position.z;
	float gamma = interpolation.z / v2.position.z;

	//透视矫正
	vertex.position.z = 1 / (alpha + beta + gamma);

	return true;//保证之后走到ZTest那里
}