#pragma once
#include "Camera.h"

class Light : public Camera {

public:
	float intensity;

	Light(const Camera& lightCamera, float intensity = 1);

	virtual void UpdateLight(const Transform& t, float aspect, float nearPlane, float farPlane, float fov, float intensity, bool isPerspective) = 0;

};

//ֱ�߹�
class DirectionLight : public Light{

public:

	DirectionLight(const Camera& lightCamera = { {}, false, 1, 1, 50, 168.6 }, float intensity = 1)
		: Light{ lightCamera, intensity }
	{};
	//DirectionLight(const Vector3f& pos, const Vector3f& dir, float i, bool forV = true);
	//��Ϊʲôû���ض������⣬��Ϊ���ڲ��ķ������壬�������ʽinline
	~DirectionLight();

	Vector3f GetDirection(Vector3f aimPos = Vector3f(0, 0, 0)) const;

	void UpdateLight(const Transform& t, float aspect, float nearPlane, float farPlane, float fov, float intensity, bool isPerspective) override;

};


//���Դ
class PointLight : public Light{

public :

	PointLight(const Camera& lightCamera = { {}, false, 1, 1, 50, 168.6 }, float intensity = 1)
		: Light{ lightCamera, intensity } {};

	~PointLight() {};

	Vector3f GetDirection(const Vector3f& aimPos) const;

	void UpdateLight(const Transform& t, float aspect, float nearPlane, float farPlane, float fov, float intensity, bool isPerspective) override;
};


//��Ϊʲôû�д�������ض��壬���ȶ���ͬһ�����뵥Ԫ�����ǵġ��ඨ�塱д����ͷ�ļ����ͷ�ļ�������ֹ�ظ�չ��
//��Σ����ඨ�塱���� class Transform { ... };�����������������������߱�������Ľṹ��Ϣ����Ա�����������ȣ������������ͽṹ��������Ŀ���ļ���.o �� .obj�������ɿ����ӵķ��š�

