#pragma once

#include <iostream>
#include <vector>
#include <string>

struct Puntos {
	double x;
	double y;
	double z;
};

class TAPLinearInterpolation {

	std::vector<Puntos> coordenadasV;
	std::vector<double> coordenadasT;

public:
	TAPLinearInterpolation();
	TAPLinearInterpolation(std::string archivoTXT);
	TAPLinearInterpolation(std::vector<Puntos> coordV, std::vector<double> coordX);
	TAPLinearInterpolation(const TAPLinearInterpolation &interpolacion);

	Puntos getPosicionInterpolada(double _t);

	~TAPLinearInterpolation();
};

