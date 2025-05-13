#include "Transform.h"
#include "MyMath.h"

Transform::Transform() 
	:position(0, 0, 0), rotation(0, 0, 0), scale(1, 1, 1), objectToWorld(){}

Transform::Transform(const Vector3f& pos, const Vector3f& rot, const Vector3f& s) 
	:position(), rotation(), scale(), objectToWorld()
{

	Scale(s);
	Rotate(rot);
	Translate(pos);

}

Transform::~Transform() {};

Matrix Transform::Translate(const Vector3f& translate) {
	Matrix tem;

	tem.matrix[0][3] = translate.x;
	tem.matrix[0][3] = translate.y;
	tem.matrix[0][3] = translate.z;

	this->objectToWorld = tem * this->objectToWorld;
	this->GetXAxis();
	this->GetYAxis();
	this->GetZAxis();

	this->position = tem * this->position;

	return this->objectToWorld;
}


Matrix Transform::Rotate(const Vector3f& rotate) {

	Matrix tem = RotateZ(rotate.z) * RotateY(rotate.y) * RotateX(rotate.x);

	this->objectToWorld = tem * this->objectToWorld;
	this->GetXAxis();
	this->GetYAxis();
	this->GetZAxis();

	this->rotation = rotate + this->rotation;

	return tem;
}

Matrix Transform::RotateX(const float& rangle){
	Matrix tem;
	tem.matrix[1][1] = std::cos((rangle * PI) / 180); tem.matrix[1][2] = -std::sin((rangle * PI) / 180);
	tem.matrix[2][1] = std::sin((rangle * PI) / 180); tem.matrix[2][2] = std::cos((rangle * PI) / 180);

	this->objectToWorld = this->objectToWorld * tem;
	this->GetXAxis();
	this->GetYAxis();
	this->GetZAxis();

	this->rotation.x += rangle;

	return tem;
}

Matrix Transform::RotateY(const float& rangle){
	Matrix tem;
	tem.matrix[0][0] = std::cos((rangle * PI) / 180); tem.matrix[0][2] = std::sin((rangle * PI) / 180);
	tem.matrix[2][0] = -std::sin((rangle * PI) / 180); tem.matrix[2][2] = std::cos((rangle * PI) / 180);

	this->objectToWorld = tem * this->objectToWorld;
	this->GetXAxis();
	this->GetYAxis();
	this->GetZAxis();

	this->rotation.y += rangle;

	return tem;
}

Matrix Transform::RotateZ(const float& rangle){
	Matrix tem;
	tem.matrix[0][0] = std::cos((rangle * PI) / 180); tem.matrix[0][1] = -std::sin((rangle * PI) / 180);
	tem.matrix[1][0] = std::sin((rangle * PI) / 180); tem.matrix[1][1] = std::cos((rangle * PI) / 180);

	this->objectToWorld = tem * this->objectToWorld;
	this->GetXAxis();
	this->GetYAxis();
	this->GetZAxis();

	this->rotation.z += rangle;

	return tem;
}

Matrix Transform::Scale(const Vector3f& scale){
	Matrix tem;
	tem.matrix[0][0] = scale.x;
	tem.matrix[1][1] = scale.y;
	tem.matrix[2][2] = scale.z;

	this->objectToWorld = tem * this->objectToWorld;
	this->GetXAxis();
	this->GetYAxis();
	this->GetZAxis();

	return Matrix();
}

void Transform::GetXAxis()
{
	this->xAxis = this->objectToWorld * Vector3f(1, 0, 0, 0);

}

void Transform::GetYAxis()
{
	this->yAxis = this->objectToWorld * Vector3f(0, 1, 0, 0);
}

void Transform::GetZAxis()
{
	this->zAxis = this->objectToWorld * Vector3f(0, 0, 1, 0);
}


