#include "Pag3DGroup.h"
#include "PagRevolutionObject.h"

/**
 * Funcion para pintar en nube de puntos todos los Pag3DElements que tenga
 * el Group
 */
void Pag3DGroup::drawPointsCloud(glm::mat4 _ViewProjectionMatrix) {
	for (int i = 0; i < numObjects; i++) {
		elements[i]->drawPointsCloud(_ViewProjectionMatrix);
	}
}

/**
* Funcion para pintar en modo solido todos los Pag3DElements que tenga
* el Group
*/
void Pag3DGroup::drawSolid(glm::mat4 _ViewProjectionMatrix){
	for (int i = 0; i < numObjects; i++) {
		elements[i]->drawSolid(_ViewProjectionMatrix);
	}
}

/**
 * Constructor por defectos de Pag3DGroup
 */
Pag3DGroup::Pag3DGroup() : elements(nullptr), numObjects(0) {
	ModelMatrix = glm::mat4(1.0f);
}

/**
 * Constructor pasandole un conjunto de Ficheros txt
 */
Pag3DGroup::Pag3DGroup(Structs::Fichero ficheros[], int _numObjects) : numObjects(_numObjects) {
	ModelMatrix = glm::mat4(1.0f);
	elements = new Pag3DElement*[numObjects];
	for (int i = 0; i < numObjects; i++) {
		elements[i] = new PagRevolutionObject(ficheros[i]);
	}
}

/**
 *  Constructor pasandole un conjunto de objetos Pag3DGroup
 */
Pag3DGroup::Pag3DGroup(Pag3DGroup groups[], int _numObjects) : numObjects(0) {
	ModelMatrix = glm::mat4(1.0f);
	elements = new Pag3DElement*[_numObjects];
	for (int i = 0; i < _numObjects; i++) { elements[i] = new Pag3DGroup(groups[i]); }
}

/**
 * Constructor de copia de Pag3DGroup
 */
Pag3DGroup::Pag3DGroup(const Pag3DGroup& orig) : numObjects(orig.numObjects) {
	ModelMatrix = glm::mat4(1.0f);
	ModelMatrix *= orig.ModelMatrix;
	elements = new Pag3DElement*[numObjects];
	for (int i = 0; i < numObjects; i++) {
		PagRevolutionObject* object = dynamic_cast<PagRevolutionObject*>(orig.elements[i]);
		if (object != nullptr) {
			elements[i] = new PagRevolutionObject(*object);
		}
	}
}

/**
 * Operador igual de Pag3DGroup
 */
void Pag3DGroup::operator=(const Pag3DGroup& orig) {
	ModelMatrix = glm::mat4(1.0f);
	ModelMatrix *= orig.ModelMatrix;
	numObjects = orig.numObjects;
	elements = new Pag3DElement*[numObjects];
	for (int i = 0; i < numObjects; i++) {
		PagRevolutionObject* object = dynamic_cast<PagRevolutionObject*>(orig.elements[i]);
		if (object != nullptr) {
			elements[i] = new PagRevolutionObject(*object);
		}
	}
}

/**
 * Funcion que crea los distintos Pag3DElements que tenga el Group
 */
void Pag3DGroup::createObject() {
	for (int i = 0; i < numObjects; i++) {
		elements[i]->createObject();
	}
}

/**
 * Destructor de Pag3DGroup
 */
Pag3DGroup::~Pag3DGroup() {
	for (int i = 0; i < numObjects; i++) {
		delete elements[i];
	}
	delete[] elements;
}
