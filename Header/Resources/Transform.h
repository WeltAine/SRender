#pragma once

#include "../Math/Vector.h"
#include "../Math/Matrix.h"


//这里采取左手坐标系
class Transform {

public:

	Vector3f position;//模型在世界空间下的中心坐标
	Vector3f rotation;//旋转
	Vector3f scale;//比例
	//这三者为模型的初态记录

	//三个单位轴向
	Vector3f xAxis = Vector3f(1, 0, 0, 0);
	Vector3f yAxis = Vector3f(0, 1, 0, 0);
	Vector3f zAxis = Vector3f(0, 0, 1, 0);

	Matrix objectToWorld;//记录所有的变换，M

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

