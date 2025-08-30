#pragma once

#include "../Resources/Transform.h"
#include "../Math/Matrix.h"
#include <tuple>
#include <memory>
//#include "Buffer.h"

struct DepthBuffer;
struct ColorBuffer;

class Camera {

public:
	Transform transform;//����Z��Ϊ��ǰ����
	float aspect, nearPlane, farPlane, fov;
	Matrix v, p;//�õ�һ��[-1. 1]�����η���������
	bool isPerspective = true;

	std::shared_ptr<DepthBuffer> zBuffer;
	std::shared_ptr<ColorBuffer> cBuffer;


	/// <summary>
	/// �������
	/// </summary>
	/// <param name="t">transform</param>
	/// <param name="isPerspective">mode</param>
	/// <param name="aspect">����</param>
	/// <param name="nearPlane">��ƽ��</param>
	/// <param name="farPlane">Զƽ��</param>
	/// <param name="fov">��׶��ֱ�н�</param>
	Camera(const Transform& t, bool isPerspective, float aspect, float nearPlane, float farPlane, float fov);


	~Camera() {
	};

	void UpdateCamera(const Transform& t, bool isPerspective, float aspect, float nearPlane, float farPlane, float fov);

	//View�������
	Matrix LookAt(const Vector3f& eyePos, const Vector3f& lookDir, const Vector3f& upAxis);

	//Perspective�������
	Matrix Perspective(float fov, float aspect, float nearPlane, float farPlane);//����Ϊ��׶��ֱ�н�(�Ƕ���)���ӿڱ�������/�ߣ��� ��ƽ����룬Զƽ�����
	Matrix Perspective(float l, float r, float t, float b, float n, float f);
	Matrix Orthographic(float l, float r, float t, float b, float n, float f);
	Matrix Orthographic(float fov, float aspect, float nearPlane, float farPlane);


};
