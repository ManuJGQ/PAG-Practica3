#pragma once

#include <GL/glew.h> //glew SIEMPRE va antes del glfw
#include <GLFW/glfw3.h>
#include "gtc\matrix_transform.hpp"

class PagCamera{
	glm::mat4 ProjectionMatrix;
	glm::mat4 ViewMatrix;
	double x;
	double y;
	double z;
	double mouseX;
	double mouseY;
public:
	PagCamera();
	PagCamera(double x, double y);
	void mover(double movX, double movY);
	glm::mat4 getViewProjectionMatrix() const { return ProjectionMatrix * ViewMatrix; }

	~PagCamera();
};

