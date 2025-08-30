#include "../../Header/Scene Entities/Camera.h"
#include "../../Header/Resources/Buffer.h"
#include "../../Header/Math/MyMath.h"


Camera::Camera(const Transform& t, bool isPerspective, float aspect, float nearPlane, float farPlane, float fov)
	:
	transform{ t },
	v{ LookAt(t.position, t.zAxis, t.yAxis) },
	p{ isPerspective ? Perspective(fov, aspect, nearPlane, farPlane) : Orthographic(fov, aspect, nearPlane, farPlane) } {

	this->aspect = aspect;
	this->nearPlane = nearPlane;
	this->farPlane = farPlane;
	this->fov = fov;
	this->isPerspective = isPerspective;

	cBuffer = std::make_shared<ColorBuffer>(512, int(512 * aspect), this);
	zBuffer = std::make_shared<DepthBuffer>(512, int(512 * aspect), this);

};



/// <summary>
/// 返回V
/// </summary>
/// <param name="eyePos"></param>
/// <param name="lookDir"></param>
/// <param name="upAxis"></param>
/// <returns></returns>
Matrix Camera::LookAt(const Vector3f& eyePos, const Vector3f& lookDir, const Vector3f& upAxis)
{
	Vector3f xAxis = Vector3f::Cross(upAxis, lookDir).Normalized();
	Vector3f yAxis = Vector3f::Cross(lookDir, xAxis).Normalized();
	Vector3f zAxis = lookDir.Normalized();

	Matrix _v_t;//逆平移
	_v_t.matrix[0][3] = -eyePos.x;
	_v_t.matrix[1][3] = -eyePos.y;
	_v_t.matrix[2][3] = -eyePos.z;

	Matrix _v_r;//逆旋转
	_v_r.matrix[0][0] = xAxis.x; _v_r.matrix[0][1] = xAxis.y; _v_r.matrix[0][2] = xAxis.z; _v_r.matrix[0][3] = 0;
	_v_r.matrix[1][0] = yAxis.x; _v_r.matrix[1][1] = yAxis.y; _v_r.matrix[1][2] = yAxis.z; _v_r.matrix[1][3] = 0;
	_v_r.matrix[2][0] = zAxis.x; _v_r.matrix[2][1] = zAxis.y; _v_r.matrix[2][2] = zAxis.z; _v_r.matrix[2][3] = 0;
	_v_r.matrix[3][0] = 0;	     _v_r.matrix[3][1] = 0;		  _v_r.matrix[3][2] = 0;	   _v_r.matrix[3][3] = 1;

	Matrix tem;
	tem.matrix[2][2] = -1;

	this->v = tem * _v_r * _v_t;

	return v;
}


/// <summary>
/// 计算P矩阵，fov为垂直方向上角度，aspect为窗口宽高比，得到2*2*2的未齐次化坐标（仍是梯形）
/// </summary>
/// <param name="fov"></param>
/// <param name="aspect"></param>
/// <param name="nearPlane"></param>
/// <param name="farPlane"></param>
/// <returns></returns>
Matrix Camera::Perspective(float fov, float aspect, float nearPlane, float farPlane)
{
	float tanHalfFov = std::tan(0.5 * fov * PI / 180);

	Matrix _p;

	_p.matrix[0][0] = 1 / (tanHalfFov * aspect); 
												_p.matrix[1][1] = 1 / tanHalfFov;
																				 _p.matrix[2][2] = (farPlane + nearPlane) / (farPlane - nearPlane); _p.matrix[2][3] = -2 * nearPlane * farPlane / (farPlane - nearPlane);
																				 _p.matrix[3][2] = -1;												_p.matrix[3][3] = 0;
	
	this->p = _p;

	return p;
}



/// <summary>
/// 计算投影P矩阵，得到2*2*2的未齐次化坐标（仍是梯形）
/// </summary>
/// <param name="l"></param>
/// <param name="r"></param>
/// <param name="t"></param>
/// <param name="b"></param>
/// <param name="n"></param>
/// <param name="f"></param>
/// <returns></returns>
Matrix Camera::Perspective(float l, float r, float t, float b, float n, float f)
{
	Matrix _p;

	_p.matrix[0][0] = 2 * n / (r - l);
										_p.matrix[1][1] = 2 * n / (t - b);
																			_p.matrix[2][2] = -(f + n) / (f - n); _p.matrix[2][3] = -2 * n * f / (f - n);
																			_p.matrix[3][2] = -1;				 _p.matrix[3][3] = 0;

	this->p = _p;

	return p;
}

/// <summary>
/// 计算正交P矩阵，得到2*2*2的立方体
/// </summary>
/// <param name="l"></param>
/// <param name="r"></param>
/// <param name="t"></param>
/// <param name="b"></param>
/// <param name="n"></param>
/// <param name="f"></param>
/// <returns></returns>
Matrix Camera::Orthographic(float l, float r, float t, float b, float n, float f)
{
	Matrix _p;

	_p.matrix[0][0] = 2 / (r - l);																 _p.matrix[0][3] = -(r + l) / (r - l);
								   _p.matrix[1][1] = 2 / (t - b);								 _p.matrix[1][3] = -(t + b) / (t - b);
																  _p.matrix[2][2] = -2 / (f - n); _p.matrix[2][3] = (f + n)/ (f - n);
																  _p.matrix[3][2] = 0;			 _p.matrix[3][3] = 1;

	this->p = _p;

	return p;
}



Matrix Camera::Orthographic(float fov, float aspect, float nearPlane, float farPlane)
{
	float l, r, t, b, n, f;

	float tanHalfFov = std::tan(0.5 * fov * PI / 180);

	r = this->nearPlane * tanHalfFov * this->aspect; l = -r;
	t = this->nearPlane * tanHalfFov; b = -t;
	n = nearPlane, f = farPlane;

	Matrix _p;

	_p.matrix[0][0] = 2 / (r - l);																  _p.matrix[0][3] = -(r + l) / (r - l);
								  _p.matrix[1][1] = 2 / (t - b);								  _p.matrix[1][3] = -(t + b) / (t - b);
																 _p.matrix[2][2] = -2 / (f - n);  _p.matrix[2][3] = (f + n) / (f - n);
																 _p.matrix[3][2] = 0;			  _p.matrix[3][3] = 1;

	this->p = _p;

	return p;
}

/// <summary>
/// 更新相机状态，所有属性都会更新,tong
/// </summary>
/// <param name="t"></param>
/// <param name="isPerspective"></param>
/// <param name="aspect"></param>
/// <param name="nearPlane"></param>
/// <param name="farPlane"></param>
/// <param name="fov"></param>
void Camera::UpdateCamera(const Transform& t, bool isPerspective, float aspect, float nearPlane, float farPlane, float fov) {

	this->transform = t;
	this->v = LookAt(t.position, t.zAxis, t.yAxis);
	this->isPerspective = isPerspective;
	this->p = isPerspective ? Perspective(fov, aspect, nearPlane, farPlane) : Orthographic(fov, aspect, nearPlane, farPlane);

	this->aspect = aspect;
	this->nearPlane = nearPlane;
	this->farPlane = farPlane;
	this->fov = fov;

}
