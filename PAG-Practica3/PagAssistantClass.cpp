#include "PagAssistantClass.h"

#include <fstream>
#include <string>

#define Epsilon 0.000001

/**
 * Constructor por defectos de PagAssistantClass
 */
PagAssistantClass::PagAssistantClass(){}

/**
 * Funcion encargada de leer ficheros txt del disco
 */
PagRevolutionObject PagAssistantClass::leerDatos(Structs::Fichero _fichero) const {
	int slices = _fichero.numSlices;
	std::string nombreAlumno = _fichero.nombreAlumno;
	std::string archivo = _fichero.archivoIN;
	bool flagBottomTape = false;
	bool flagTopTape = false;

	int linea;
	linea = nombreAlumno.find('-');
	nombreAlumno = nombreAlumno.substr(0, linea);

	std::string linea_actual;
	int numPuntosPerfilOriginal;
	int numDivisiones;
	int coma;
	try {
		// Leemos la primera linea del archivo
		std::ifstream archivoPuntosPerfil;
		archivoPuntosPerfil.open(archivo);

		if (!archivoPuntosPerfil.good()) throw std::string("No se puedo leer el archivo");

		std::getline(archivoPuntosPerfil, linea_actual);
		coma = linea_actual.find(',');
		numPuntosPerfilOriginal = stoi(linea_actual.substr(0, coma));
		numDivisiones = stoi(linea_actual.substr(coma + 1, linea_actual.length()));

		if (numPuntosPerfilOriginal < 2) throw std::string("Se necesitan 2 o mas puntos");
		if (numDivisiones < 0) throw std::string("No se permite un numero negativo de divisiones");

		PuntosPerfil *perfil = new PuntosPerfil[numPuntosPerfilOriginal];
		PuntosPerfil puntos;

		for (int i = 0; i < numPuntosPerfilOriginal; i++) {
			//Leemos los puntos del Perfil
			std::getline(archivoPuntosPerfil, linea_actual);
			coma = linea_actual.find(',');
			puntos.x = stof(linea_actual.substr(0, coma));

			if ((puntos.x < 0) ||
				(puntos.x == 0 && (i > 0 && i < numPuntosPerfilOriginal - 1))) {
				numPuntosPerfilOriginal--;
				i--;
			}
			else {
				if (puntos.x == 0) {
					if (i == 0) flagBottomTape = true;
					if (i == numPuntosPerfilOriginal - 1) flagTopTape = true;
				}

				puntos.y = stof(linea_actual.substr(coma + 1, linea_actual.length()));

				perfil[i] = puntos;

			}

		}

		archivoPuntosPerfil.close();

		PuntosPerfil *perfilTemp = new PuntosPerfil[numPuntosPerfilOriginal];
		for (int i = 0; i < numPuntosPerfilOriginal; i++) {
			perfilTemp[i] = perfil[i];
		}

		delete[] perfil;

		perfil = perfilTemp;

		return PagRevolutionObject(numPuntosPerfilOriginal, numDivisiones, perfil,
			flagBottomTape, flagTopTape, slices, nombreAlumno);

	}
	catch (std::string &e) {
		std::cout << "ERROR: " << e << std::endl;
	}
}

/**
 * Funcion encargada de escribir los ficheros txt en disco
 */
void PagAssistantClass::devolverDatos(const PagRevolutionObject &object, std::string nombreAlumno) {
	Geometria *geometria = &object.getGeometria();
	CoordTexturas *coordtext = &object.getCoordText();
	int *indices = &object.getIndices();
	int tamaGeometriaCoordText = object.getTamaGeometriaCoordText();
	int tamaIndices = object.getTamaIndices();
	int tamIndicesTapes = object.getTamaIndicesTapes();

	char* docdir = getenv("userprofile");
	std::string path = docdir;
	path += "/Desktop/";
	path += nombreAlumno;
	std::string nombreFichero;

	//ARCHIVO GEOMETRIA

	nombreFichero = path;
	nombreFichero += "-out-geom.txt";
	std::ofstream ficheroGeom;
	ficheroGeom.open(nombreFichero);
	ficheroGeom << tamaGeometriaCoordText << std::endl;
	for (int i = 0; i < tamaGeometriaCoordText; i++) {
		ficheroGeom << geometria[i].vertice.x << ","
			<< geometria[i].vertice.y << ","
			<< geometria[i].vertice.z << ","
			<< geometria[i].normal.x << ","
			<< geometria[i].normal.y << ","
			<< geometria[i].normal.z << ","
			<< geometria[i].tangente.x << ","
			<< geometria[i].tangente.y << ","
			<< geometria[i].tangente.z << std::endl;
	}
	ficheroGeom.close();

	//ARCHIVO COORDTEXT

	nombreFichero = path;
	nombreFichero += "-out-text.txt";
	std::ofstream ficheroText;
	ficheroText.open(nombreFichero);
	ficheroText << tamaGeometriaCoordText << std::endl;
	for (int i = 0; i < tamaGeometriaCoordText; i++) {
		ficheroText << coordtext[i].s << ","
			<< coordtext[i].t << std::endl;
	}
	ficheroText.close();

	//ARCHIVOS INDICES

	nombreFichero = path;
	nombreFichero += "-out-ind.txt";
	std::ofstream ficheroInd;
	ficheroInd.open(nombreFichero);
	ficheroInd << tamaIndices << std::endl;
	for (int i = 0; i < tamaIndices; i++) {
		ficheroInd << indices[i] << std::endl;
	}
	ficheroInd.close();

	if (object.getFlagBottomTape()) {
		int *indicesBottom = &object.getIndicesBottomTape();
		nombreFichero = path;
		nombreFichero += "-out-ind_BottomTape.txt";
		std::ofstream ficheroIndBottom;
		ficheroIndBottom.open(nombreFichero);
		ficheroIndBottom << tamIndicesTapes << std::endl;
		for (int i = 0; i < tamIndicesTapes; i++) {
			ficheroIndBottom << indicesBottom[i] << std::endl;
		}
		ficheroInd.close();
	}

	if (object.getFlagTopTape()) {
		int *indicesTop = &object.getIndicesTopTape();
		nombreFichero = path;
		nombreFichero += "-out-ind_TopTape.txt";
		std::ofstream ficheroIndTop;
		ficheroIndTop.open(nombreFichero);
		ficheroIndTop << tamIndicesTapes << std::endl;
		for (int i = 0; i < tamIndicesTapes; i++) {
			ficheroIndTop << indicesTop[i] << std::endl;
		}
		ficheroIndTop.close();
	}
}

/**
* Destructor de Pag3AssistantClass
*/
PagAssistantClass::~PagAssistantClass() {}
