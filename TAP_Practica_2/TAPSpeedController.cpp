#include "TAPSpeedController.h"

#include <glut.h>
#include <iostream>
#include <math.h>

static float PI = 3.14159265359;

/**
* Constructor por defecto
*/
TAPSpeedController::TAPSpeedController(){
	k1 = 0.0f;
	k2 = 0.0f;
	actualizarF();
}

/**
* Constructor parametrizado
*/
TAPSpeedController::TAPSpeedController(float _k1, float _k2){
	k1 = _k1;
	k2 = _k2;
	actualizarF();
}

/**
* Constructor de copia
*/
TAPSpeedController::TAPSpeedController(const TAPSpeedController & speedcontroller){
	k1 = speedcontroller.k1;
	k2 = speedcontroller.k2;
	f = speedcontroller.f;
}

/**
* Funcion la cual dado un t (entre 0 y 1) te devuleve la distancia
* s recorrida por el objeto en cuestion
*/
float TAPSpeedController::ease(float t){
	float s = 0.0f;
	
	if (t < k1) {
		s = k1 * (2 / PI) * (sin((t / k1) * (2 / PI) - (2 / PI)) + 1);
	}
	else if (t < k2) {
		s = (2 * k1 / PI) + t - k1;
	}
	else {
		s = (2 * k1 / PI) + k2 - k1 + ((1.0f - k2) * (2 / PI)) * sin(((t - k2) / (1.0f - k2)) * (2 / PI));
	}
	
	return s / f;
}

/**
* Recalcula la variable f usada para calcular la distancia s
*/
void TAPSpeedController::actualizarF(){
	f = k1 * (2 / PI) + k2 - k1 + (1.0f - k2) * (2 / PI);
}


void TAPSpeedController::pintarCurva(){
	for (float i = 0.0f; i <= 1.0f; i += 0.001) {
		float p = ease(i);
		glPushMatrix();
			glTranslatef(i * 10 - (k1 / 2), p * 10 - (k1 / 2), 0.0f);

			glPushMatrix();
				GLfloat color[] = { 1.0,0.0,0.0 };
				glMaterialfv(GL_FRONT, GL_EMISSION, color);

				glutSolidSphere(0.1, 20, 20);
			glPopMatrix();
		glPopMatrix();
	}

	float p = ease(k1);

	glPushMatrix();
		glTranslatef(k1 * 10 - (k1 / 2), p * 10 - (k1 / 2), 0.0f);

		glPushMatrix();
			GLfloat color[] = { 0.0,0.0,0.0 };
			glMaterialfv(GL_FRONT, GL_EMISSION, color);

			glutSolidSphere(0.5, 20, 20);
		glPopMatrix();
	glPopMatrix();

	p = ease(k2);

	glPushMatrix();
		glTranslatef(k2 * 10 - (k1 / 2), p * 10 - (k1 / 2), 0.0f);

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
TAPSpeedController::~TAPSpeedController(){}
