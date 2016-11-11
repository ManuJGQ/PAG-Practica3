#pragma once

#include "Structs.h"
#include "Pag3DElement.h"

class Pag3DGroup : public Pag3DElement {
	Pag3DElement** elements;
	int numObjects;
	glm::mat4 ModelMatrix;
public:
	void drawPointsCloud(glm::mat4 ViewProjectionMatrix) override;
	void drawSolid(glm::mat4 ViewProjectionMatrix) override;
	void createObject() override;
	Pag3DGroup();
	Pag3DGroup(Structs::Fichero ficheros[], int _numObjects);
	Pag3DGroup(Pag3DGroup groups[], int _numObjects);
	Pag3DGroup(const Pag3DGroup &orig);
	void operator = (const Pag3DGroup &orig);
	~Pag3DGroup();
};

