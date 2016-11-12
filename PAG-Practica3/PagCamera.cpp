#include "PagCamera.h"

PagCamera::PagCamera(){
	x = 20.0;
	y = 20.0;
	z = -20.0;
	ProjectionMatrix *= glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.f);
	ViewMatrix *= glm::lookAt(glm::vec3(20.0, 20.0, -20.0),
		glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
}

void PagCamera::mover(double movX){
	x += movX;
	ViewMatrix *= glm::lookAt(glm::vec3(20.0 + movX, 20.0, -20.0),
		glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
}

PagCamera::~PagCamera(){}
