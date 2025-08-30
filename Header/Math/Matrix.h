#pragma once

#include "Vector.h"

class Vertex;

class Matrix {

public:
	float matrix[4][4] = {0};

	Matrix();
	~Matrix();

	//都是返回一个新的矩阵。不会更改原来的矩阵
	Matrix operator + (const Matrix& rightMatrix) const;
	Matrix operator - (const Matrix& rightMatrix) const;
	Matrix operator * (const Matrix& rightMatrix) const;
	Vector3f operator * (const Vector3f& rightVector3f) const;
	Matrix operator * (const float value) const;
	
	Vector3f MatrixMultiplyVector3(const Vector3f& rightVector3f) const;

	static Matrix Identity();

	Matrix Transpose() const;

	void Print() const;

};



