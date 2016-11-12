#include <iostream>

#include "PagCamera.h"

PagCamera::PagCamera(): mouseX(0), mouseY(0) {
	x = 20.0;
	y = 20.0;
	z = -20.0;
	ProjectionMatrix *= glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.f);
	ViewMatrix *= glm::lookAt(glm::vec3(x, y, z),
	                          glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
}

PagCamera::PagCamera(double _x, double _y): mouseX(_x), mouseY(_y) {
	x = 20.0;
	y = 20.0;
	z = -20.0;
	ProjectionMatrix *= glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.f);
	ViewMatrix *= glm::lookAt(glm::vec3(x, y, z),
	                          glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
}

void PagCamera::mover(double movX , double movY){
	double xtemp = mouseX - movX;
	xtemp = xtemp / 4;
	x += xtemp;
	mouseX = movX;
	double ytemp = mouseY - movY;
	ytemp = ytemp / 4;
	y += ytemp;
	mouseY = movY;
	std::cout << x << " - " << y << std::endl;
 	ViewMatrix = glm::lookAt(glm::vec3(x, y, z),
		glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
}

PagCamera::~PagCamera(){}
