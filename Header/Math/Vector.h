#pragma once

#include <iostream>
#include <windows.h>
#include <math.h>

template <typename T>
class Vector3 {
public:
	//����
	T x, y, z, w;//Ϊ��ʵ����ȫ�����Ա任������ʵ�����ĸ�ά��
	float magnitude;

	//��ʼ��
	Vector3(T x, T y, T z, T w);
	Vector3(T x, T y, T z);
	Vector3();

	//����
	Vector3<T> operator + (const Vector3<T>& otherVector3) const;
	Vector3<T> operator - (const Vector3<T>& otherVector3) const;
	Vector3<T> operator * (float value) const;
	Vector3<T> operator / (float value) const;
	static Vector3<T> LerpVector3(const Vector3<T>& p1, const Vector3<T>& p2, float t);

	//���
	float Dot(const Vector3<T>& rightVector3) const;
	static float Dot(const Vector3<T>& leftVector3, const Vector3<T>& rightVebtor3);

	//���
	Vector3<T> Cross(const Vector3<T>& rightVector3) const;
	static Vector3<T> Cross(const Vector3<T>& leftVector3, const Vector3<T>& rightVector3);

	//���Ժ���
	float Magnitude();
	float SquareMagnitude();//ģ��ƽ��
	Vector3<T>& Normalize();
	Vector3<T> Normalized() const;

	//����Vector��Ψһһ���ı�w�ķ���
	Vector3& Standardization() {
		if (w != 0) {

			this->x = x / w;
			this->y = y / w;
			this->z = z / w;
			this->w = 1;
		}

		return *this;
	};

	template<typename U>
	bool operator == (const Vector3<U>& aim) const;
};

//inline �ĺ�������
//�����������ÿ����������������������ֱ��Ƕ����ô������һ��չ������������ת��ջ�������Ƿ����������ɱ�����������ȡ�����Ż����𡢺������Ӷȵȣ���
//����ͷ�ļ��ж��庯�������Ϊ inline �ĺ��������ڶ�����뵥Ԫ��.cpp �ļ������ظ�����(������ͬһ��ͷ�ļ�)�����������Զ�ѡ��һ��ʵ�֡������������Ϊ inline������������Զ�����뵥Ԫ�е��ظ����壬������һ�ݣ���cherno˵����ͷ�ļ���Ϊ��������inline�� Ҳ���ڱ�����ֱ�Ӹ��ƴ��룬����Ҳ�ܹ���ض������⣩��
//δ�� inline ����ͨ������ͷ�ļ��ж���ᵼ�����Ӵ����ظ����壩��


//��ģ�屾��ÿ��ʵ��������ʱҲֻ������һ����inline�ƺ�������Ҫ
template<typename T>
Vector3<T>::Vector3(T x, T y, T z, T w)
	:x{ x }, y{ y }, z{ z }, w{ w }, magnitude{ this->Magnitude() }//��ȷ�����ʱ���Ƿ���У�����
{
}

template<typename T>
Vector3<T>::Vector3(T x, T y, T z)
	: x{ x }, y{ y }, z{ z }, w{ 1 }, magnitude{ this->Magnitude() }
{
}

template<typename T>
Vector3<T>::Vector3()
	: x{ 0 }, y{ 0 }, z{ 0 }, w{ 1 }, magnitude{ 0 }
{
}

template<typename T>
Vector3<T> Vector3<T>::operator+(const Vector3<T>& otherVector3) const
{
	T _x = this->x + otherVector3.x;
	T _y = this->y + otherVector3.y;
	T _z = this->z + otherVector3.z;
	return Vector3<T>(_x, _y, _z);
}

template<typename T>
Vector3<T> Vector3<T>::operator-(const Vector3<T>& otherVector3) const
{
	T _x = this->x - otherVector3.x;
	T _y = this->y - otherVector3.y;
	T _z = this->z - otherVector3.z;
	return Vector3<T>(_x, _y, _z);
}

template<typename T>
Vector3<T> Vector3<T>::operator*(float value) const
{
	T _x = this->x * value;
	T _y = this->y * value;
	T _z = this->z * value;
	return Vector3<T>(_x, _y, _z, this->w);
}

template<typename T>
Vector3<T> Vector3<T>::operator/(float value) const
{
	T _x = this->x / value;
	T _y = this->y / value;
	T _z = this->z / value;
	return Vector3<T>(_x, _y, _z, this->w);
}

template<typename T>
Vector3<T> Vector3<T>::LerpVector3(const Vector3<T>& p1, const Vector3<T>& p2, float t) {
	return (p1 * (1 - t)) + (p2 * t);
}

template<typename T>
float Vector3<T>::Dot(const Vector3<T>& rightVector3) const
{
	return (this->x * rightVector3.x + this->y * rightVector3.y + this->z * rightVector3.z);
}

template<typename T>
float Vector3<T>::Dot(const Vector3<T>& leftVector3, const Vector3<T>& rightVector3)
{
	return (leftVector3.x * rightVector3.x + leftVector3.y * rightVector3.y + leftVector3.z * rightVector3.z);
}

template<typename T>
Vector3<T> Vector3<T>::Cross(const Vector3<T>& rightVector3) const
{
	T _x = (this->y * rightVector3.z - this->z * rightVector3.y);
	T _y = (this->z * rightVector3.x - this->x * rightVector3.z);
	T _z = (this->x * rightVector3.y - this->y * rightVector3.x);
	return Vector3<T>(_x, _y, _z);
}

template<typename T>
Vector3<T> Vector3<T>::Cross(const Vector3<T>& leftVector3, const Vector3<T>& rightVector3)
{
	T _x = (leftVector3.y * rightVector3.z - leftVector3.z * rightVector3.y);
	T _y = (leftVector3.z * rightVector3.x - leftVector3.x * rightVector3.z);
	T _z = (leftVector3.x * rightVector3.y - leftVector3.y * rightVector3.x);
	return Vector3<T>(_x, _y, _z);
}

template<typename T>
float Vector3<T>::Magnitude()
{
	return std::sqrt(Vector3<T>::Dot(*this, *this));
}

template<typename T>
float Vector3<T>::SquareMagnitude()
{
	return Vector3<T>::Dot(*this, *this);
}

template<typename T>
Vector3<T>& Vector3<T>::Normalize()
{
	*this = *this / this->magnitude;//Ӧ�ò��������ڴ����⣬/����Ľ������ջ�ϵģ�����thisָ���˶ѣ��Ǹ��ѿռ䲢���ᱻ�ͷ�
	this->magnitude = 1;
	return *this;
}

template<typename T>
Vector3<T> Vector3<T>::Normalized() const
{
	return *this / this->magnitude;
}

template<typename T>
template<typename U>
inline bool Vector3<T>::operator==(const Vector3<U>& aim) const
{
	//����
	Vector3<T> tem_1 = *this;
	Vector3<U> tem_2 = aim;

	//��λ�
	tem_1.Standardization();
	tem_2.Standardization();

	return tem_1.x == tem_2.x && tem_1.y == tem_2.y && tem_1.z == tem_2.z;
}


using Vector3f = Vector3<float>;
using Vector3i = Vector3<int>;



template<typename T>
class Vector2 {

public:
	T x = 0, y = 0;

	Vector2();
	Vector2(const T& inX, const T& inY);
	~Vector2();

	Vector2<T> operator + (const Vector2<T>& rightVector2) const;
	Vector2<T> operator - (const Vector2<T>& rightVector2) const;
	Vector2<T> operator * (const Vector2<T>& rightVector2) const;
	Vector2<T> operator / (const Vector2<T>& rightVector2) const;

	Vector2<T> operator + (const T& value) const;
	Vector2<T> operator - (const T& value) const;
	Vector2<T> operator * (const T& value) const;
	Vector2<T> operator / (const T& value) const;

	template<typename U>
	bool operator == (const Vector2<U>& aim) const;

};

template<typename T>
Vector2<T>::Vector2()
	:x(0), y(0){}

template<typename T>
Vector2<T>::Vector2(const T& inX, const T& inY)
	:x(inX), y(inY) {}

template<typename T>
Vector2<T>::~Vector2() {}

template<typename T>
Vector2<T> Vector2<T>::operator+(const Vector2<T>& rightVector2) const{
	Vector2 tem;

	tem.x = this->x + rightVector2.x;
	tem.y = this->y + rightVector2.y;

	return tem;
}

template<typename T>
Vector2<T> Vector2<T>::operator-(const Vector2<T>& rightVector2) const {
	Vector2 tem;

	tem.x = this->x - rightVector2.x;
	tem.y = this->y - rightVector2.y;

	return tem;
}

template<typename T>
Vector2<T> Vector2<T>::operator*(const Vector2<T>& rightVector2) const {
	Vector2 tem;

	tem.x = this->x * rightVector2.x;
	tem.y = this->y * rightVector2.y;

	return tem;
}

template<typename T>
Vector2<T> Vector2<T>::operator/(const Vector2<T>& rightVector2) const {
	Vector2 tem;

	tem.x = this->x / rightVector2.x;
	tem.y = this->y / rightVector2.y;

	return tem;
}

template<typename T>
Vector2<T> Vector2<T>::operator+(const T& value) const {
	Vector2 tem;

	tem.x = this->x + value;
	tem.y = this->y + value;

	return tem;
}

template<typename T>
Vector2<T> Vector2<T>::operator-(const T& value) const {
	Vector2 tem;

	tem.x = this->x - value;
	tem.y = this->y - value;

	return tem;
}

template<typename T>
Vector2<T> Vector2<T>::operator*(const T& value) const {
	Vector2 tem;

	tem.x = this->x * value;
	tem.y = this->y * value;

	return tem;
}

template<typename T>
Vector2<T> Vector2<T>::operator/(const T& value) const {
	Vector2 tem;

	tem.x = this->x / value;
	tem.y = this->y / value;

	return tem;
}


using Vector2f = Vector2<float>;
using Vector2i = Vector2<int>;

template<typename T>
template<typename U>
inline bool Vector2<T>::operator==(const Vector2<U>& aim) const
{
	return this->x == aim.x && this->y == aim.y;
}
