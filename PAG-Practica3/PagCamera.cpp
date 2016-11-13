#include <iostream>

#include "PagCamera.h"

PagCamera::PagCamera() : mouseX(0), mouseY(0), rotates(false) {
	x = 0.0;
	y = 0.0;
	z = -30.0;
	xLookAt = 0.0;
	yLookAt = 0.0;
	zLookAt = 0.0;
	fovY = 45.0f;
	ProjectionMatrix *= glm::perspective(fovY, 4.0f / 3.0f, 0.1f, 100.f);
	ViewMatrix *= glm::lookAt(glm::vec3(x, y, z),
		glm::vec3(xLookAt, yLookAt, zLookAt), glm::vec3(0.0, 1.0, 0.0));
}

PagCamera::PagCamera(double _x, double _y) : mouseX(512), mouseY(384), rotates(false) {
	x = 0.0;
	y = 0.0;
	z = -30.0;
	xLookAt = 0.0;
	yLookAt = 0.0;
	zLookAt = 0.0;
	fovY = 45.0f;
	ProjectionMatrix *= glm::perspective(fovY, 4.0f / 3.0f, 0.1f, 100.f);
	ViewMatrix *= glm::lookAt(glm::vec3(x, y, z),
		glm::vec3(xLookAt, yLookAt, zLookAt), glm::vec3(0.0, 1.0, 0.0));
}

void PagCamera::mover(double movX, double movY) {
	if (rotates) {
		double xtemp = mouseX - movX;
		xtemp = xtemp / 4;
		mouseX = movX;
		xLookAt += xtemp;
		double ytemp = mouseY - movY;
		ytemp = ytemp / 4;
		yLookAt += ytemp;
		mouseY = movY;
	}
	else {
		double xtemp = mouseX - movX;
		xtemp = xtemp / 4;
		x += xtemp;
		mouseX = movX;
		xLookAt += xtemp;
		double ytemp = mouseY - movY;
		ytemp = ytemp / 4;
		y += ytemp;
		yLookAt += ytemp;
		mouseY = movY;
		std::cout << x << " - " << y << std::endl;
	}
	ViewMatrix = glm::lookAt(glm::vec3(x, y, z),
		glm::vec3(xLookAt, yLookAt, zLookAt), glm::vec3(0.0, 1.0, 0.0));
}

void PagCamera::zoom(double _zoom){
	_zoom = _zoom / 4;
	fovY += _zoom;
	ProjectionMatrix = glm::perspective(fovY, 4.0f / 3.0f, 0.1f, 100.f);
}

PagCamera::~PagCamera() {}
