#pragma once

#include <iostream>
#include "glm.hpp"

namespace Structs {
	struct PuntosPerfil {
		double x;
		double y;
	};

	struct PuntosVertices {
		double x;
		double y;
		double z;
	};

	struct NormalesTangentes {
		double x;
		double y;
		double z;
	};

	struct CoordTexturas {
		double s;
		double t;
	};

	struct Geometria {
		PuntosVertices vertice;
		NormalesTangentes normal;
		NormalesTangentes tangente;
	};

	struct Fichero {
		std::string archivoIN;
		int numSlices;
		std::string nombreAlumno;
	};

	struct PagPositionColor {
		glm::vec3 position;
		glm::vec3 color;
	};

}
