#include "Light.h"

//DirectionLight::DirectionLight(Camera lightCamera = { {}, false, 1, 1, 50, 84.3 }, float intensity = 1)
//	:position{}, direction{ 1, 1, 1, 0 }, intensity{ 1 }, forVertex{true}
//{
//	direction.Normalize();
//}

//DirectionLight::DirectionLight(const Vector3f& pos, const Vector3f& dir, float i, bool forV)
//	:position{ pos }, direction{ dir }, intensity{ i }, forVertex{forV}
//{
//	direction.Normalize();
//}

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

//Matrix DirectionLight::LookAt(const Vector3f& upAxis) const
//{
//	//？这里并没有像Unity一样采取以－Z为观看方向，原因未知，或许是根本不需要
//	Vector3f xAxis = Vector3f::Cross(upAxis.Normalized(), direction);
//	Vector3f yAxis = Vector3f::Cross(direction, xAxis);
//
//	Matrix tem;
//	//写错了，注意这里不是将空间转移到新的正交坐标基，而是将正交坐标基转移到空间，所以要用到逆，正好，正交举证的逆就是转置
//	//tem.matrix[0][0] = xAxis.x; tem.matrix[0][1] = yAxis.x; tem.matrix[0][2] = direction.x; tem.matrix[0][3] = 0;
//	//tem.matrix[1][0] = xAxis.y; tem.matrix[1][1] = yAxis.y; tem.matrix[1][2] = direction.y; tem.matrix[1][3] = 0;
//	//tem.matrix[2][0] = xAxis.z; tem.matrix[2][1] = yAxis.z; tem.matrix[2][2] = direction.z; tem.matrix[2][3] = 0;
//	//tem.matrix[3][0] = 0; tem.matrix[3][1] = 0; tem.matrix[3][2] = 0; tem.matrix[3][3] = 1;
//
//	tem.matrix[0][0] = xAxis.x;		tem.matrix[0][1] = xAxis.y;		tem.matrix[0][2] = xAxis.z;		tem.matrix[0][3] = -position.x;
//	tem.matrix[1][0] = yAxis.x;		tem.matrix[1][1] = yAxis.y;		tem.matrix[1][2] = yAxis.z;		tem.matrix[1][3] = -position.y;
//	tem.matrix[2][0] = direction.x; tem.matrix[2][1] = direction.y; tem.matrix[2][2] = direction.z; tem.matrix[2][3] = -position.z;
//	tem.matrix[3][0] = 0;			tem.matrix[3][1] = 0;			tem.matrix[3][2] = 0;			tem.matrix[3][3] = 1;
//
//
//	return tem;
//}


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
