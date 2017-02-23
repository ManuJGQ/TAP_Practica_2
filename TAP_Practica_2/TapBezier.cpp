#include "TapBezier.h"
#include <math.h>

TapBezier::TapBezier() {
	curva = std::vector<Structs::PuntosVertices>();
};

TapBezier::TapBezier(Structs::PuntosVertices _pa, Structs::PuntosVertices _pb, 
	Structs::PuntosVertices _pc, Structs::PuntosVertices _pd): 
	pa(_pa), pb(_pb), pc(_pc), pd(_pd) {
	curva = std::vector<Structs::PuntosVertices>();
};

void TapBezier::createObject() {
	for (double i = 0; i <= 1.0; i += 0.01) {
		Structs::PuntosVertices pt;

		double b1 = pow((1-i),3);
		double b2 = 3 * i * pow((1-i),2);
		double b3 = 3 * pow(i,2) * (1-i);
		double b4 = pow(i,3);

		pt.x = pa.x * b1 + pc.x * b2 + pd.x * b3 + pb.x * b4;
		pt.y = pa.y * b1 + pc.y * b2 + pd.y * b3 + pb.y * b4;
		pt.z = pa.z * b1 + pc.z * b2 + pd.z * b3 + pb.z * b4;

		//std::cout << pt.x << " " << pt.y << " " << pt.z << " - " << i << " - " << t << std::endl;

		curva.push_back(pt);
	}
};

TapBezier::~TapBezier(){}
