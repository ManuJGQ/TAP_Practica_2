#include "TAPLinearInterpolation.h"

#include <fstream>

/**
* Constructor por defecto de la interpolacion lineal
*/
TAPLinearInterpolation::TAPLinearInterpolation(){
	coordenadasV = std::vector<Puntos>();
	coordenadasT = std::vector<double>();
}

/**
* Constructor que crea la interpolacion a partir de un fichero .txt
*/
TAPLinearInterpolation::TAPLinearInterpolation(std::string archivoTXT) {
	coordenadasV = std::vector<Puntos>();
	coordenadasT = std::vector<double>();

	int coma;
	std::string linea_actual;

	double T;
	std::string sV;
	Puntos V;

	try {
		std::ifstream archivoInterpolacion;
		archivoInterpolacion.open(archivoTXT);

		if (!archivoInterpolacion.good()) throw std::string("No se puedo leer el archivo");

		std::getline(archivoInterpolacion, linea_actual);
		while (!linea_actual.empty()) {
			coma = linea_actual.find(',');

			T = std::stod(linea_actual.substr(0, coma));

			sV = linea_actual.substr(coma + 1, linea_actual.length());

			coma = sV.find(',');

			V.x = std::stod(sV.substr(0, coma));

			sV = sV.substr(coma + 1, sV.length());

			coma = sV.find(',');

			V.y = std::stod(sV.substr(0, coma));

			sV = sV.substr(coma + 1, sV.length());

			coma = sV.find(',');

			V.z = std::stod(sV.substr(0, coma));

			sV = sV.substr(coma + 1, sV.length());

			coordenadasT.push_back(T);
			coordenadasV.push_back(V);

			std::getline(archivoInterpolacion, linea_actual);
		}

	}
	catch (std::string &e) {
		throw e;
	}
}

/**
* Constructor que crea la interpolacion a partir de dos vectores
*/
TAPLinearInterpolation::TAPLinearInterpolation(std::vector<Puntos> coordV, std::vector<double> coordT){
	coordenadasV = std::vector<Puntos>();
	coordenadasT = std::vector<double>();

	for (int i = 0; i < coordV.size(); i++) {
		coordenadasT.push_back(coordT[i]);
		coordenadasV.push_back(coordV[i]);
	}
}

/**
* Constructor de copia
*/
TAPLinearInterpolation::TAPLinearInterpolation(const TAPLinearInterpolation & interpolacion){
	coordenadasV = std::vector<Puntos>();
	coordenadasT = std::vector<double>();

	for (int i = 0; i < interpolacion.coordenadasT.size(); i++) {
		coordenadasT.push_back(interpolacion.coordenadasT[i]);
		coordenadasV.push_back(interpolacion.coordenadasV[i]);
	}
}

Puntos TAPLinearInterpolation::getPosicionInterpolada(double _t){

	return Puntos();
}

/**
* Destructor
*/
TAPLinearInterpolation::~TAPLinearInterpolation(){}
