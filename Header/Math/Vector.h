#pragma once

#include <iostream>
#include <windows.h>
#include <math.h>

template <typename T>
class Vector3 {
public:
	//属性
	T x, y, z, w;//为了实现完全的线性变换，所以实际上四个维度
	float magnitude;

	//初始化
	Vector3(T x, T y, T z, T w);
	Vector3(T x, T y, T z);
	Vector3();

	//运算
	Vector3<T> operator + (const Vector3<T>& otherVector3) const;
	Vector3<T> operator - (const Vector3<T>& otherVector3) const;
	Vector3<T> operator * (float value) const;
	Vector3<T> operator / (float value) const;
	static Vector3<T> LerpVector3(const Vector3<T>& p1, const Vector3<T>& p2, float t);

	//点积
	float Dot(const Vector3<T>& rightVector3) const;
	static float Dot(const Vector3<T>& leftVector3, const Vector3<T>& rightVebtor3);

	//叉积
	Vector3<T> Cross(const Vector3<T>& rightVector3) const;
	static Vector3<T> Cross(const Vector3<T>& leftVector3, const Vector3<T>& rightVector3);

	//属性函数
	float Magnitude();
	float SquareMagnitude();//模的平方
	Vector3<T>& Normalize();
	Vector3<T> Normalized() const;

	//这是Vector中唯一一个改变w的方法
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

//inline 的核心作用
//消除函数调用开销：建议编译器将函数体直接嵌入调用处（像宏一样展开），避免跳转和栈操作。是否真正内联由编译器决定（取决于优化级别、函数复杂度等）。
//允许头文件中定义函数：标记为 inline 的函数可以在多个编译单元（.cpp 文件）中重复定义(都引入同一个头文件)，链接器会自动选择一份实现。若函数被标记为 inline，链接器会忽略多个编译单元中的重复定义，仅保留一份（但cherno说过，头文件里为定义设置inline， 也是在编译期直接复制代码，这样也能规避重定义问题）。
//未加 inline 的普通函数在头文件中定义会导致链接错误（重复定义）。


//但模板本身每种实例在链接时也只会留下一个，inline似乎不再重要
template<typename T>
Vector3<T>::Vector3(T x, T y, T z, T w)
	:x{ x }, y{ y }, z{ z }, w{ w }, magnitude{ this->Magnitude() }//不确定这个时机是否可行，可行
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
	*this = *this / this->magnitude;//应该不会引发内存问题，/运算的结果是在栈上的，哪怕this指向了堆，那个堆空间并不会被释放
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
	//复制
	Vector3<T> tem_1 = *this;
	Vector3<U> tem_2 = aim;

	//齐次化
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
