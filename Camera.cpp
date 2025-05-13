#include "Camera.h"
#include "MyMath.h"


Matrix Camera::LookAt(const Vector3f& eyePos, const Vector3f& lookDir, const Vector3f& upAxis)
{
	Vector3f xAxis = Vector3f::Cross(lookDir, upAxis).Normalized();
	Vector3f yAxis = Vector3f::Cross(lookDir, xAxis).Normalized();
	Vector3f zAxis = lookDir.Normalized();

	Matrix _v;
	_v.matrix[0][0] = xAxis.x; _v.matrix[0][1] = xAxis.y; _v.matrix[0][2] = xAxis.z; _v.matrix[0][3] = -eyePos.x;
	_v.matrix[1][0] = yAxis.x; _v.matrix[1][1] = yAxis.y; _v.matrix[1][2] = yAxis.z; _v.matrix[1][3] = -eyePos.y;
	_v.matrix[2][0] = zAxis.x; _v.matrix[2][1] = zAxis.y; _v.matrix[2][2] = zAxis.z; _v.matrix[2][3] = -eyePos.z;
	_v.matrix[3][0] = 0;	   _v.matrix[3][1] = 0;		  _v.matrix[3][2] = 0;		 _v.matrix[3][3] = 1;

	this->v = _v;

	return v;
}

Matrix Camera::Perspective(float fov, float aspect, float nearPlane, float farPlane)
{
	float tanHalfFov = std::tan(0.5 * fov * PI / 180);

	Matrix _p;

	_p.matrix[0][0] = 1 / (tanHalfFov * aspect); 
												_p.matrix[1][1] = 1 / tanHalfFov;
																				 _p.matrix[2][2] = (farPlane + nearPlane) / (farPlane - nearPlane); _p.matrix[2][3] = -2 * nearPlane * farPlane / (farPlane - nearPlane);
																				 _p.matrix[3][2] = 1;												_p.matrix[3][3] = 0;//？这一行和原项目参数不一样，不知道那个-1怎么算出来的
	
	this->p = _p;

	return p;
}

Matrix Camera::Perspective(float l, float r, float t, float b, float n, float f)
{
	Matrix _p;

	_p.matrix[0][0] = 2 * n / (r - l);
										_p.matrix[1][1] = 2 * n / (t - b);
																			_p.matrix[2][2] = (f + n) / (f - n); _p.matrix[2][3] = -2 * n * f / (f - n);
																			_p.matrix[3][2] = 1;				 _p.matrix[3][3] = 0;

	this->p = _p;

	return p;
}

Matrix Camera::Orthographic(float l, float r, float t, float b, float n, float f)
{
	Matrix _p;

	_p.matrix[0][0] = 2 / (r - l);																 _p.matrix[0][3] = -(r + l) / (r - l);
								   _p.matrix[1][1] = 2 / (t - b);								 _p.matrix[1][3] = -(t + b) / (t - b);
																  _p.matrix[2][2] = 2 / (f - n); _p.matrix[2][3] = -(f + n)/ (f - n);
																								 _p.matrix[3][3] = 0;

	this->p = _p;

	return p;
}
