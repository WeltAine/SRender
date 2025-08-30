#pragma once

#include "../Math/Vector.h"
#include "../Math/Matrix.h"


//�����ȡ��������ϵ
class Transform {

public:

	Vector3f position;//ģ��������ռ��µ���������
	Vector3f rotation;//��ת
	Vector3f scale;//����
	//������Ϊģ�͵ĳ�̬��¼

	//������λ����
	Vector3f xAxis = Vector3f(1, 0, 0, 0);
	Vector3f yAxis = Vector3f(0, 1, 0, 0);
	Vector3f zAxis = Vector3f(0, 0, 1, 0);

	Matrix objectToWorld;//��¼���еı任��M

	Transform();
	Transform(const Vector3f& pos, const Vector3f& rot, const Vector3f& s);
	~Transform();

	Matrix Translate(const Vector3f& translate);
	
	Matrix Rotate(const Vector3f& rotate);
	Matrix RotateX(const float& rangle);
	Matrix RotateY(const float& rangle);
	Matrix RotateZ(const float& rangle);

	Matrix Scale(const Vector3f& scale);


	Vector3f UpdateXAxis();
	Vector3f UpdateYAxis();
	Vector3f UpdateZAxis();

};

