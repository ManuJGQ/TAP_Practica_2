#include "TAPSphericalInterpolation.h"

#include <fstream>
#include <math.h>

#define Epsilon 0.000001

static bool iguales(double a, double b) {
	return (abs(a - b) <= Epsilon);
}

/**
* Constructor por defecto de la interpolacion esferica
*/
TAPSphericalInterpolation::TAPSphericalInterpolation(){
	coordenadasV = std::vector<Quaternion>();
	coordenadasT = std::vector<double>();
}

/**
* Constructor que crea la interpolacion a partir de un fichero .txt
* con el siguiente formato en cada linea:
* t,v Ejemplo: 0.6,1,1,1,1 tiene t = 0.6 y Quaternion = 1,1,1,1
*/
TAPSphericalInterpolation::TAPSphericalInterpolation(std::string archivoTXT){
	coordenadasV = std::vector<Quaternion>();
	coordenadasT = std::vector<double>();

	int coma;
	std::string linea_actual;

	double T;
	std::string sV;
	Quaternion V;

	try {
		std::ifstream archivoInterpolacion;
		archivoInterpolacion.open(archivoTXT);

		if (!archivoInterpolacion.good()) throw std::string("No se puedo leer el archivo");

		while (std::getline(archivoInterpolacion, linea_actual)) {
			coma = linea_actual.find(',');

			T = std::stod(linea_actual.substr(0, coma));

			sV = linea_actual.substr(coma + 1, linea_actual.length());

			coma = sV.find(',');

			V.s = std::stod(sV.substr(0, coma));

			sV = sV.substr(coma + 1, sV.length());

			coma = sV.find(',');

			V.x = std::stod(sV.substr(0, coma));

			sV = sV.substr(coma + 1, sV.length());

			coma = sV.find(',');

			V.y = std::stod(sV.substr(0, coma));

			sV = sV.substr(coma + 1, sV.length());

			coma = sV.find(',');

			V.z = std::stod(sV.substr(0, coma));

			sV = sV.substr(coma + 1, sV.length());

			std::cout << T << " - " << V.s << "," << V.x << "," << V.y << "," << V.z << "," << std::endl;

			coordenadasT.push_back(T);
			coordenadasV.push_back(V);

		}

	}
	catch (std::string &e) {
		throw e;
	}
}

/**
* Constructor que crea la interpolacion a partir de dos vectores
*/
TAPSphericalInterpolation::TAPSphericalInterpolation(std::vector<Quaternion> coordV, std::vector<double> coordT){
	coordenadasV = std::vector<Quaternion>();
	coordenadasT = std::vector<double>();

	for (int i = 0; i < coordV.size(); i++) {
		coordenadasT.push_back(coordT[i]);
		coordenadasV.push_back(coordV[i]);
	}
}

/**
* Constructor de copia
*/
TAPSphericalInterpolation::TAPSphericalInterpolation(const TAPSphericalInterpolation & interpolacion){
	coordenadasV = std::vector<Quaternion>();
	coordenadasT = std::vector<double>();

	for (int i = 0; i < interpolacion.coordenadasT.size(); i++) {
		coordenadasT.push_back(interpolacion.coordenadasT[i]);
		coordenadasV.push_back(interpolacion.coordenadasV[i]);
	}
}

/**
* Funcion que dado un valor T devuelve el Quaternion en funcion a la interpolacion
*/
Quaternion TAPSphericalInterpolation::getPosicionInterpolada(double _t){

	return Quaternion();
}

/**
* Funcion que calcula el Quaternion en un instante t comprendido entre el comienzo y el
* final de dos interpolaciones esfericas distintas
*/
Quaternion TAPSphericalInterpolation::getPosicionInterpolada(const TAPSphericalInterpolation & interpolacion){

	return Quaternion();
}


TAPSphericalInterpolation::~TAPSphericalInterpolation(){}
