#pragma once


#include <vector>
#include "Structs.h"

class TapBezier {

	Structs::PuntosVertices pa;
	Structs::PuntosVertices pb;
	Structs::PuntosVertices pc;
	Structs::PuntosVertices pd;

	std::vector<Structs::PuntosVertices> curva;

public:

	TapBezier();
	TapBezier(Structs::PuntosVertices _pa, Structs::PuntosVertices _pb, Structs::PuntosVertices _pc,
		Structs::PuntosVertices _pd);
	void createObject() ;
	~TapBezier();
};

