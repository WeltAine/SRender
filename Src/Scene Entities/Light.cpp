#include "../../Header/Scene Entities/Light.h"
#include "../../Header/Resources/Buffer.h"

Light::Light(const Camera& lightCamera, float intensity)
	: Camera{ lightCamera }, intensity{ intensity }
{
	this->zBuffer->aimCamera = this;
	this->cBuffer->aimCamera = this;
}


DirectionLight::~DirectionLight()
{
}

/// <summary>
/// 获得世界空间中光源到目标点的距离向量，默认是到原点的距离向量
/// </summary>
/// <param name="aimPos"></param>
/// <returns></returns>
Vector3f DirectionLight::GetDirection(Vector3f aimPos) const
{
	Vector3f tem = aimPos - this->transform.position;
	tem.w = 0;
	return tem;
}



/// <summary>
/// 更新光源的相机与强度
/// </summary>
/// <param name="t"></param>
/// <param name="isPerspective"></param>
/// <param name="aspect"></param>
/// <param name="nearPlane"></param>
/// <param name="farPlane"></param>
/// <param name="fov"></param>
/// <param name="intensity"></param>
void DirectionLight::UpdateLight(const Transform& t, float aspect, float nearPlane, float farPlane, float fov, float intensity, bool isPerspective = false) {
	this->UpdateCamera(t, false, aspect, nearPlane, farPlane, fov);
	this->intensity = intensity;
}






Vector3f PointLight::GetDirection(const Vector3f& aimPos) const
{
	Vector3f tem = aimPos - this->transform.position;
	tem.w = 0;
	return tem;
}

/// <summary>
/// 更新光源的相机与强度
/// </summary>
/// <param name="t"></param>
/// <param name="aspect"></param>
/// <param name="nearPlane"></param>
/// <param name="farPlane"></param>
/// <param name="fov"></param>
/// <param name="intensity"></param>
/// <param name="isPerspective"></param>
void PointLight::UpdateLight(const Transform& t, float aspect, float nearPlane, float farPlane, float fov, float intensity, bool isPerspective = true)
{
	this->UpdateCamera(t, true, aspect, nearPlane, farPlane, fov);
	this->intensity = intensity;

}
