#pragma once

#include <iostream>
#include <vector>

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
	~TAPLinearInterpolation();
};

