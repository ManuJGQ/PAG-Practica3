#include "PagCamera.h"

#include <math.h>

#define PI 3.14159265358979323846

PagCamera::PagCamera() : mouseX(0), mouseY(0), rotates(false), truck(false), orbit(false) {
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

PagCamera::PagCamera(double _x, double _y) : mouseX(512), mouseY(384), rotates(false), truck(false), orbit(false) {
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
	if(!orbit) {
		if (rotates) {
			double xtemp = mouseX - movX;
			xtemp = xtemp / 16;
			mouseX = movX;
			xLookAt += xtemp;
			double ytemp = mouseY - movY;
			ytemp = ytemp / 16;
			yLookAt += ytemp;
			mouseY = movY;
		}
		else if (truck) {
			double ztemp = mouseY - movY;
			ztemp = ztemp / 16;
			zLookAt += ztemp;
			z += ztemp;
			mouseY = movY;
		}
		else {
			double xtemp = mouseX - movX;
			xtemp = xtemp / 16;
			x += xtemp;
			mouseX = movX;
			xLookAt += xtemp;
			double ytemp = mouseY - movY;
			ytemp = ytemp / 16;
			y += ytemp;
			yLookAt += ytemp;
			mouseY = movY;
		}
		ViewMatrix = glm::lookAt(glm::vec3(x, y, z),
			glm::vec3(xLookAt, yLookAt, zLookAt), glm::vec3(0.0, 1.0, 0.0));
	}
}

void PagCamera::movOrbit(){
	x = 0.0;
	y = 10.0;
	z = -30.0;
	xLookAt = 0.0;
	yLookAt = 0.0;
	zLookAt = 0.0;
	fovY = 45.0f;
	ProjectionMatrix = glm::perspective(fovY, 4.0f / 3.0f, 0.1f, 100.f);
	ViewMatrix = glm::lookAt(glm::vec3(x, y, z),
		glm::vec3(xLookAt, yLookAt, zLookAt), glm::vec3(0.0, 1.0, 0.0));

	double angleRadIncrement = (2 * PI) / 100;

	while (orbit) {
		double xtemp = x;
		//double ztemp = z;
		for(int i=0;i<100;i++) {
			x = xtemp * cos(angleRadIncrement * i);
			z = x * -sin(angleRadIncrement * i);
			ViewMatrix = glm::lookAt(glm::vec3(x, y, z),
				glm::vec3(xLookAt, yLookAt, zLookAt), glm::vec3(0.0, 1.0, 0.0));
			if (!orbit)break;
		}
	}
}

void PagCamera::zoom(double _zoom) {
	_zoom = _zoom / 50;
	fovY += _zoom;
	ProjectionMatrix = glm::perspective(fovY, 4.0f / 3.0f, 0.1f, 100.f);
}

PagCamera::~PagCamera() {}
