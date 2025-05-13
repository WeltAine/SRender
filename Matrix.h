#pragma once

#include "Vector.h"

class Matrix {

public:
	float matrix[4][4] = {0};

	Matrix();
	~Matrix();

	
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
