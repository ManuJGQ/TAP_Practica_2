#ifndef __IGVESCENA3D
#define __IGVESCENA3D

#include <glut.h>

#include <iostream>
#include "TAPMotionController.h"

#define Epsilon 0.000001

static bool iguales(double a, double b) {
	return (abs(a - b) <= Epsilon);
}

using namespace std;

class igvEscena3D {
	Punto movimiento;

	float twist;
protected:	
	bool ejes;
	bool tapering;
public:
	// Constructores por defecto y destructor
	igvEscena3D();
	~igvEscena3D();

	// Metodos estáticos

	// Métodos
	// método con las llamadas OpenGL para visualizar la escena
	void visualizar(void);

	void setMovimiento(Punto _mov) {
		movimiento.x = _mov.x;
		movimiento.y = _mov.y;
		movimiento.z = _mov.z;
	}

	void setTwist(float _t) {
		float tw = twist + _t;
		if ((tw > -0.78 || iguales(tw, -0.78)) && (tw < 0.78 || iguales(tw, 0.78)) && !tapering) {
			twist += _t;
		}
	}

	bool get_ejes() { return ejes; };
	void set_ejes(bool _ejes) { ejes = _ejes; };

	bool getTapering() { return tapering; }
	void setTapering(bool _t) { tapering = _t; }
};

#endif
