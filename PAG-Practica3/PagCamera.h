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
public:
	PagCamera();
	void mover(double movX);
	glm::mat4 getViewProjectionMatrix() const { return ProjectionMatrix * ViewMatrix; }
	double getX() const { return x; }

	~PagCamera();
};

