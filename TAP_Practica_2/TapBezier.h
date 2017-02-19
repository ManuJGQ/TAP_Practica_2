#pragma once


#include <vector>
#include "Structs.h"

class TapBezier{

	Structs::PuntosVertices pa;
	Structs::PuntosVertices pb;
	Structs::PuntosVertices pc;
	Structs::PuntosVertices pd;

	std::vector<Structs::PuntosVertices> curva;

	int numPuntos;

public:

	TapBezier();
	TapBezier(Structs::PuntosVertices _pa, Structs::PuntosVertices _pb, Structs::PuntosVertices _pc,
		Structs::PuntosVertices _pd, int _numPuntos);
	void crearCurva();
	~TapBezier();
};

