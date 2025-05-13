#include "Light.h"

DirectionLight::DirectionLight()
	:position{}, direction{ 1, 1, 1, 0 }, intensity{ 1 }, forVertex{true}
{
	direction.Normalize();
}

DirectionLight::DirectionLight(const Vector3f& pos, const Vector3f& dir, float i, bool forV)
	:position{ pos }, direction{ dir }, intensity{ i }, forVertex{forV}
{
	direction.Normalize();
}

DirectionLight::~DirectionLight()
{
}

Vector3f DirectionLight::GetDirection(Vector3f aimPos) const
{
	return Vector3f(0, 0, 0) - this->direction;//返回的结果已经单位化
}

Matrix DirectionLight::LookAt(const Vector3f& upAxis) const
{
	//？这里并没有像Unity一样采取以－Z为观看方向，原因未知，或许是根本不需要
	Vector3f xAxis = Vector3f::Cross(upAxis.Normalized(), direction);
	Vector3f yAxis = Vector3f::Cross(direction, xAxis);

	Matrix tem;
	//写错了，注意这里不是将空间转移到新的正交坐标基，而是将正交坐标基转移到空间，所以要用到逆，正好，正交举证的逆就是转置
	//tem.matrix[0][0] = xAxis.x; tem.matrix[0][1] = yAxis.x; tem.matrix[0][2] = direction.x; tem.matrix[0][3] = 0;
	//tem.matrix[1][0] = xAxis.y; tem.matrix[1][1] = yAxis.y; tem.matrix[1][2] = direction.y; tem.matrix[1][3] = 0;
	//tem.matrix[2][0] = xAxis.z; tem.matrix[2][1] = yAxis.z; tem.matrix[2][2] = direction.z; tem.matrix[2][3] = 0;
	//tem.matrix[3][0] = 0; tem.matrix[3][1] = 0; tem.matrix[3][2] = 0; tem.matrix[3][3] = 1;

	tem.matrix[0][0] = xAxis.x;		tem.matrix[0][1] = xAxis.y;		tem.matrix[0][2] = xAxis.z;		tem.matrix[0][3] = -position.x;
	tem.matrix[1][0] = yAxis.x;		tem.matrix[1][1] = yAxis.y;		tem.matrix[1][2] = yAxis.z;		tem.matrix[1][3] = -position.y;
	tem.matrix[2][0] = direction.x; tem.matrix[2][1] = direction.y; tem.matrix[2][2] = direction.z; tem.matrix[2][3] = -position.z;
	tem.matrix[3][0] = 0;			tem.matrix[3][1] = 0;			tem.matrix[3][2] = 0;			tem.matrix[3][3] = 1;


	return tem;
}

Vector3f PointLight::GetDirection(const Vector3f& aimPos) const
{
	return this->position - aimPos;
}
