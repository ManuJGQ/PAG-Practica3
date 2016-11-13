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

	double xLookAt;
	double yLookAt;
	double zLookAt;

	float fovY;

	double mouseX;
	double mouseY;

	bool rotates;
	bool truck;
	bool orbit;
public:
	PagCamera();
	PagCamera(double x, double y);
	void mover(double movX, double movY);
	void movOrbit();
	glm::mat4 getViewProjectionMatrix() const { return ProjectionMatrix * ViewMatrix; }
	void setRotates(bool _rotates) { rotates = _rotates; }
	void setTruck(bool _truck) { truck = _truck; }
	void setOrbit(bool _orbit) { orbit = _orbit; }
	bool getOrbit() const { return orbit; }
	void zoom(double _zoom);

	~PagCamera();
};

