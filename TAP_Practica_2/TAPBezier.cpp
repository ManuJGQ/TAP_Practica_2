#include "TAPBezier.h"

#include <glui.h>

#include <math.h>

/**
* Constructor por defecto de una curva de Bezier
*/
TAPBezier::TAPBezier() {}

/**
* Constructor al cual le pasas los 4 puntos que sirven para construir
* una curva de Bezier
*/
TAPBezier::TAPBezier(Punto _a, Punto _c0, Punto _c1, Punto _b) {
	A = _a;
	C0 = _c0;
	C1 = _c1;
	B = _b;
}

/**
* Constructor el cual construye la curva de Bezier a traves de los puntos
* que lee de un fichero .txt con el siguiente formato:
* Linea 1: Punto A
* Linea 2: Punto C0
* Linea 3: Punto C1
* Linea 4: Punto B
*/
TAPBezier::TAPBezier(std::string ficheroTXT) {
	//to do: cargar por fichero
}

/**
* Constructor de copia
*/
TAPBezier::TAPBezier(const TAPBezier & bezier) {
	A = bezier.A;
	C0 = bezier.C0;
	C1 = bezier.C1;
	B = bezier.B;
}

/**
* Funcion que devuelve el punto P de la curva en el instante t
*/
Punto TAPBezier::getPunto(float u) {
	Punto p;

	float b0 = pow((1 - u), 3);
	float b1 = 3 * u * pow((1 - u), 2);
	float b2 = 3 * pow(u, 2) * (1 - u);
	float b3 = pow(u, 3);

	p.x = b0 * A.x + b1 * C0.x + b2 * C1.x + b3 * B.x;
	p.y = b0 * A.y + b1 * C0.y + b2 * C1.y + b3 * B.y;
	p.z = b0 * A.z + b1 * C0.z + b2 * C1.z + b3 * B.z;

	return p;
}

/**
* Funcion que calcula la distancia en linea recta entre los puntos
* correspondientes a los valores u1 y u2 de la curva de Bezier
*/
float TAPBezier::distancia(float u1, float u2) {
	Punto a = getPunto(u1);
	Punto b = getPunto(u2);

	return sqrt(powf(a.x - b.x, 2) + powf(a.y - b.y, 2) + powf(a.z - b.z, 2));
}

/**
* Funcion encargada de pintar la Curva de Bezier en cuestion
*/
void TAPBezier::pintarCurva() {
	for (float i = 0.0f; i <= 1.0f; i += 0.001) {
		Punto p = getPunto(i);
		glPushMatrix();
			glTranslatef(p.x, p.y, p.z);

			glPushMatrix();
				GLfloat color[] = { 1.0,0.0,0.0 };
				glMaterialfv(GL_FRONT, GL_EMISSION, color);

				glutSolidSphere(0.1, 20, 20);
			glPopMatrix();
		glPopMatrix();
	}

	glPushMatrix();
		glTranslatef(A.x, A.y, A.z);

		glPushMatrix();
			GLfloat color[] = { 0.0,0.0,0.0 };
			glMaterialfv(GL_FRONT, GL_EMISSION, color);

			glutSolidSphere(0.5, 20, 20);
		glPopMatrix();
	glPopMatrix();


	glPushMatrix();
		glTranslatef(C0.x, C0.y, C0.z);

		glPushMatrix();
			GLfloat color2[] = { 0.0,0.0,1.0 };
			glMaterialfv(GL_FRONT, GL_EMISSION, color2);

			glutSolidSphere(0.5, 20, 20);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(C1.x, C1.y, C1.z);

		glPushMatrix();
			GLfloat color3[] = { 0.0,0.0,1.0 };
			glMaterialfv(GL_FRONT, GL_EMISSION, color3);

			glutSolidSphere(0.5, 20, 20);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(B.x, B.y, B.z);

		glPushMatrix();
			GLfloat color4[] = { 0.0,0.0,0.0 };
			glMaterialfv(GL_FRONT, GL_EMISSION, color4);

			glutSolidSphere(0.5, 20, 20);
		glPopMatrix();
	glPopMatrix();

}

/**
* Destructor
*/
TAPBezier::~TAPBezier() {}
