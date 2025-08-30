#include "../../Header/Math/Matrix.h"

Matrix Matrix::Identity() {

	Matrix tem;

	return tem;
}

Matrix::Matrix() {

	for (int i = 0; i < 4; i++) {
		this->matrix[i][i] = 1;
	}

}

Matrix::~Matrix() {

}

Matrix Matrix::operator+(const Matrix& rightMatrix) const{
	Matrix tem;
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			tem.matrix[y][x] = this->matrix[y][x] + rightMatrix.matrix[y][x];
		}
	}
	return tem;
}

Matrix Matrix:: operator - (const Matrix& rightMatrix) const{
	Matrix tem;
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			tem.matrix[y][x] = this->matrix[y][x] - rightMatrix.matrix[y][x];
		}
	}
	return tem;
}

Matrix Matrix::operator *(const Matrix& rightMatrix) const{
	Matrix tem;
	Vector3f rightVector4;
	for (int x = 0; x < 4; x++) {
		
		rightVector4.x = rightMatrix.matrix[0][x];
		rightVector4.y = rightMatrix.matrix[1][x];
		rightVector4.z = rightMatrix.matrix[2][x];
		rightVector4.w = rightMatrix.matrix[3][x];

		Vector3f temResult = this->MatrixMultiplyVector3(rightVector4);

		tem.matrix[0][x] = temResult.x;
		tem.matrix[1][x] = temResult.y;
		tem.matrix[2][x] = temResult.z;
		tem.matrix[3][x] = temResult.w;

	}

	return tem;
}

Vector3f Matrix::operator*(const Vector3f& rightVector3f) const
{
	return this->MatrixMultiplyVector3(rightVector3f);
}

Matrix Matrix::operator*(const float value) const{
	Matrix tem;
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			tem.matrix[y][x] = this->matrix[y][x] * value;
		}
	}
	return tem;
}

/// <summary>
/// ×ªÖÃ
/// </summary>
/// <returns></returns>
Matrix Matrix::Transpose() const {
	Matrix tem;
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			tem.matrix[y][x] = this->matrix[x][y];
		}
	}
	return tem;
}

Vector3f Matrix::MatrixMultiplyVector3(const Vector3f& rightVector3f) const {
	
	float v[4] = {0, 0, 0, 0};
	for (int y = 0; y < 4; y++) {

		v[y] += this->matrix[y][0] * rightVector3f.x;
		v[y] += this->matrix[y][1] * rightVector3f.y;
		v[y] += this->matrix[y][2] * rightVector3f.z;
		v[y] += this->matrix[y][3] * rightVector3f.w;

	}
	
	return Vector3f{v[0], v[1], v[2], v[3]};

}

void Matrix::Print() const {
	std::cout << "-----------------Matrix Begin--------------" << std::endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			std::cout << "[" << this->matrix[i][j] << "]   ";
		}
		std::cout << std::endl;
	}
	std::cout << "-----------------Matrix End----------------" << std::endl;

}

