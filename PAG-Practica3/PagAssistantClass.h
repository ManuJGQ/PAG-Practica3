#pragma once

#include "PagRevolutionObject.h"

class PagAssistantClass{
public:
	PagAssistantClass();
	PagRevolutionObject leerDatos(Structs::Fichero _fichero) const;
	static void devolverDatos(const Geometria *geometria, const CoordTexturas *coordtext,
		const int *indices,const int tamaGeometriaCoordText,  std::string nombreAlumno,
			const int tamaIndices, const int tamaIndicesTapes);
	~PagAssistantClass();
};

