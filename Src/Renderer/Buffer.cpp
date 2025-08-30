
#include "../../Header/Resources/Buffer.h"
#include "../../Header/Scene Entities/Camera.h"


DepthBuffer::DepthBuffer(int width, int height, Camera* aimCamera)
	: Buffer{ width, height }, aimCamera{ aimCamera }
{

	for (int i = 0; i < width * height; i++) {
		buffer[i] = aimCamera->farPlane + 0.1;
	}

}


float DepthBuffer::Sample(int x, int y) const {

	////像素中心坐标
	//int _x = Clamp(x, 0, width - 1);
	//int _y = Clamp(y, 0, height - 1);

	if (x >= width || x < 0 || y >= height || y < 0) {
		return aimCamera->farPlane;
	}

	return this->buffer[y * width + x];

}

void DepthBuffer::UpdateBuffer(int x, int y, float value) {

	if (x >= width || x < 0 || y >= height || y < 0) {
		return;
	}

	this->buffer[y * width + x] = value;


}

void DepthBuffer::ResetBuffer(int width, int height) {

	this->Buffer::ResetBuffer(width, height);

	for (int i = 0; i < width * height; i++) {
		buffer[i] = aimCamera->farPlane + 0.1;
	}

	if (this->aimCamera)
		aimCamera->UpdateCamera(this->aimCamera->transform, this->aimCamera->isPerspective, width / float(height), this->aimCamera->nearPlane, this->aimCamera->farPlane, this->aimCamera->fov);
}






ColorBuffer::ColorBuffer(int width, int height, Camera* aimCamera)
	: Buffer{ width, height }, aimCamera{ aimCamera }
{
	for (int i = 0; i < width * height; i++) {
		buffer[i] = Color::black;
	}
}


Color ColorBuffer::Sample(int x, int y) const {

	if (x >= width || x < 0 || y >= height || y < 0) {
		return Color::white;
	}

	return this->buffer[y * width + x];

}


void ColorBuffer::UpdateBuffer(int x, int y, Color value) {

	if (x >= width || x < 0 || y >= height || y < 0) {
		return;
	}

	this->buffer[y * width + x] = value;

}

void ColorBuffer::ResetBuffer(int width, int height) {

	this->Buffer::ResetBuffer(width, height);

	for (int i = 0; i < width * height; i++) {
		buffer[i] = Color::black;
	}

	if (this->aimCamera)
		aimCamera->UpdateCamera(this->aimCamera->transform, this->aimCamera->isPerspective, width / float(height), this->aimCamera->nearPlane, this->aimCamera->farPlane, this->aimCamera->fov);


}



