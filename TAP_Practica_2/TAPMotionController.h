#pragma once

#include <vector>

#include "TAPBezier.h"
#include "TAPSpeedController.h"

struct entradaTabla {
	float u;
	float s;
};

class TAPMotionController{

	int nEntradasTabla;

	TAPBezier desplazamiento;
	TAPSpeedController velocidad;

	std::vector<entradaTabla> tablaIncrementos;

public:
	TAPMotionController();
	~TAPMotionController();
};

