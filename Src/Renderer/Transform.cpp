#include "../../Header/Resources/Transform.h"
#include "../../Header/Math/MyMath.h"

Transform::Transform() 
	:position(0, 0, 0), rotation(0, 0, 0), scale(1, 1, 1), objectToWorld(){}

/// <summary>
/// 先比例后旋转，最后平移
/// </summary>
/// <param name="pos"></param>
/// <param name="rot"></param>
/// <param name="s"></param>
Transform::Transform(const Vector3f& pos, const Vector3f& rot, const Vector3f& s) 
	:position(), rotation(), scale(1, 1, 1), objectToWorld()
{

	this->Scale(s);
	this->Rotate(rot);
	this->Translate(pos);

}

Transform::~Transform() {};

/// <summary>
/// 对this进行平移
/// </summary>
/// <param name="translate"></param>
/// <returns></returns>
Matrix Transform::Translate(const Vector3f& translate) {
	Matrix tem;

	tem.matrix[0][3] = translate.x;
	tem.matrix[1][3] = translate.y;
	tem.matrix[2][3] = translate.z;

	this->objectToWorld = tem * this->objectToWorld;
	//平移无需更新
	//this->GetXAxis();
	//this->GetYAxis();
	//this->GetZAxis();

	this->position = tem * this->position;

	return this->objectToWorld;
}


/// <summary>
/// 对this进行基于世界坐标系的旋转，旋转顺序为XYZ（轴为本次旋转过程中产生的轴），参数为角度制
/// </summary>
/// <param name="rotate"></param>
/// <returns></returns>
Matrix Transform::Rotate(const Vector3f& rotate) {

	Matrix tem = RotateX(rotate.x) * RotateY(rotate.y) * RotateZ(rotate.z) ;

	//this->objectToWorld = tem * this->objectToWorld;//不需要再更新了，上一步中已经发生更新了
	//this->GetXAxis();
	//this->GetYAxis();
	//this->GetZAxis();
	//this->rotation = rotate + this->rotation;//这里也不需要了

	return tem;
}


/// <summary>
/// 对this进行绕世界X轴旋转，参数为角度制
/// </summary>
/// <param name="rangle"></param>
/// <returns></returns>
Matrix Transform::RotateX(const float& rangle){
	Matrix tem;
	tem.matrix[1][1] = std::cos((rangle * PI) / 180); tem.matrix[1][2] = -std::sin((rangle * PI) / 180);
	tem.matrix[2][1] = std::sin((rangle * PI) / 180); tem.matrix[2][2] = std::cos((rangle * PI) / 180);

	this->objectToWorld = this->objectToWorld * tem;
	this->UpdateXAxis();
	this->UpdateYAxis();
	this->UpdateZAxis();

	this->rotation.x += rangle;

	return tem;
}


/// <summary>
/// 对this进行绕世界Y轴旋转，参数为角度制
/// </summary>
/// <param name="rangle"></param>
/// <returns></returns>
Matrix Transform::RotateY(const float& rangle){
	Matrix tem;
	tem.matrix[0][0] = std::cos((rangle * PI) / 180); tem.matrix[0][2] = std::sin((rangle * PI) / 180);
	tem.matrix[2][0] = -std::sin((rangle * PI) / 180); tem.matrix[2][2] = std::cos((rangle * PI) / 180);

	this->objectToWorld = tem * this->objectToWorld;
	this->UpdateXAxis();
	this->UpdateYAxis();
	this->UpdateZAxis();

	this->rotation.y += rangle;

	return tem;
}

/// <summary>
/// 对this进行绕世界Z轴旋转，参数为角度制
/// </summary>
/// <param name="rangle"></param>
/// <returns></returns>
Matrix Transform::RotateZ(const float& rangle){
	Matrix tem;
	tem.matrix[0][0] = std::cos((rangle * PI) / 180); tem.matrix[0][1] = -std::sin((rangle * PI) / 180);
	tem.matrix[1][0] = std::sin((rangle * PI) / 180); tem.matrix[1][1] = std::cos((rangle * PI) / 180);

	this->objectToWorld = tem * this->objectToWorld;
	this->UpdateXAxis();
	this->UpdateYAxis();
	this->UpdateZAxis();

	this->rotation.z += rangle;

	return tem;
}



Matrix Transform::Scale(const Vector3f& scale){
	Matrix tem;
	tem.matrix[0][0] = scale.x;
	tem.matrix[1][1] = scale.y;
	tem.matrix[2][2] = scale.z;

	this->objectToWorld = tem * this->objectToWorld;
	//this->UpdateXAxis();
	//this->UpdateYAxis();
	//this->UpdateZAxis();

	this->scale = tem * this->scale;

	return tem;
}

Vector3f Transform::UpdateXAxis()
{
	return this->xAxis = (this->objectToWorld * Vector3f(1, 0, 0, 0)).Normalized();
}

Vector3f Transform::UpdateYAxis()
{
	return this->yAxis = (this->objectToWorld * Vector3f(0, 1, 0, 0)).Normalized();
}

Vector3f Transform::UpdateZAxis()
{
	return this->zAxis = (this->objectToWorld * Vector3f(0, 0, 1, 0)).Normalized();
}


