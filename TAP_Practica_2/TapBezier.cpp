#include "TapBezier.h"

TapBezier::TapBezier() {
	curva = std::vector<Structs::PuntosVertices>();
	numPuntos = 0;
};

TapBezier::TapBezier(Structs::PuntosVertices _pa, Structs::PuntosVertices _pb, 
	Structs::PuntosVertices _pc, Structs::PuntosVertices _pd, int _numPuntos): 
	numPuntos(_numPuntos), pa(_pa), pb(_pb), pc(_pc), pd(_pd) {
	curva = std::vector<Structs::PuntosVertices>();
};

void TapBezier::crearCurva() {
	double t = 1 / numPuntos;
	for (int i = 0; i <= 1.0; i += t) {
		Structs::PuntosVertices pt;
		//FORMULA
		//pt = (1−t)3 p1 + 3 t(1−t)2 pc + 3 t2(1−t) pd + p2 t3
		curva.push_back(pt);
	}
};

TapBezier::~TapBezier(){}
