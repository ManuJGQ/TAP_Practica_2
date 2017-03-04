#include <cstdlib>
#include <stdio.h>

#include "igvEscena3D.h"

// Metodos constructores 

igvEscena3D::igvEscena3D() {
	ejes = true;

	//inicializar los atributos para el control de los grados de libertad del modelo 

	cuerpo = 0;
	rcabeza = 0;
	rcabeza2 = 0;
	bi = 0;
	// inicializar el atributo/s que indica/n el objeto seleccionado para pintarlo de otro color

	CUERPO = 1;
	CABEZA = 2;
	OJO_IZQ = 3;
	OJO_DER = 4;
	BOCA = 5;
	SOMBRERO = 6;
	HOMBRO_IZQ = 7;
	HOMBRO_DER = 8;
	BRAZO_IZQ = 9;
	BRAZO_DER = 10;
	ART_PIERNA_IZQ = 11;
	ART_PIERNA_DER = 12;
	PIERNA_IZQ = 13;
	PIERNA_DER = 14;
	PIE_IZQ = 15;
	PIE_DER = 16;

	CUERPOS = false;
	CABEZAS = false;
	OJO_IZQS = false;
	OJO_DERS = false;
	BOCASS = false;
	SOMBREROSS = false;
	HOMBRO_IZQS = false;
	HOMBRO_DERS = false;
	BRAZO_IZQS = false;
	BRAZO_DERS = false;
	ART_PIERNA_IZQS = false;
	ART_PIERNA_DERS = false;
	PIERNA_IZQS = false;
	PIERNA_DERS = false;
	PIE_IZQS = false;
	PIE_DERS = false;

	movimiento.x = 0;
	movimiento.y = 0;
	movimiento.z = 0;

}

igvEscena3D::~igvEscena3D() {

}


// Metodos publicos 

void pintar_ejes(void) {
	GLfloat rojo[] = { 1,0,0,1.0 };
	GLfloat verde[] = { 0,1,0,1.0 };
	GLfloat azul[] = { 0,0,1,1.0 };

	glBegin(GL_LINES);
	glMaterialfv(GL_FRONT, GL_EMISSION, rojo);
	glVertex3f(1000, 0, 0);
	glVertex3f(-1000, 0, 0);

	glMaterialfv(GL_FRONT, GL_EMISSION, verde);
	glVertex3f(0, 1000, 0);
	glVertex3f(0, -1000, 0);

	glMaterialfv(GL_FRONT, GL_EMISSION, azul);
	glVertex3f(0, 0, 1000);
	glVertex3f(0, 0, -1000);
	glEnd();
}


void igvEscena3D::visualizar() {
	// crear luces
	GLfloat luz0[4] = { 5.0,5.0,5.0,1 }; // luz puntual  
	glLightfv(GL_LIGHT0, GL_POSITION, luz0); // la luz se coloca aquí si permanece fija y no se mueve con la escena
	glEnable(GL_LIGHT0);

	// crear el modelo
	glPushMatrix(); // guarda la matriz de modelado

	  // se pintan los ejes
	if (ejes) pintar_ejes();

	//glLightfv(GL_LIGHT0,GL_POSITION,luz0); // la luz se coloca aquí si se mueve junto con la escena

//aquí hay que añadir la visualización del árbol del modelo utilizando la pila de matrices de OpenGL
//            se recomienda crear una método auxiliar que encapsule todo el código para la visualización
//           del modelo, dejando aquí sólo la llamada a ese método. En el apartado D hay que añadir los nombres
//	          a las partes móviles del objeto mediante la pila de nombres y el control del objeto seleccionado 
//						para colorearlo en amarillo
	glTranslated(movimiento.x, movimiento.y, movimiento.z);
	glRotatef(giro.s, giro.x, giro.y, giro.z);

	pintarGrafo();

	glPopMatrix(); // restaura la matriz de modelado
}

void igvEscena3D::pintarGrafo() {
	//glRotatef(cuerpo, 0, 1, 0);
	double k = cuerpo;
	double z = 0.5;
	double x = 1 * cos(k * z) - 1.5 * sin(k * z);
	double y = 1 * sin(k * z) + 1.5 * cos(k * z);
	cout << x << " " << y << " " << z << " " << k << endl;
	if (CUERPOS)glScaled(x, y, z);

	glPushName(CUERPO);
	tronco();						//CUERPO
	glPopName();
	glPushMatrix();						//CABEZA COMPLETA

	glRotatef(rcabeza, 0, 1, 0);
	glRotatef(rcabeza2, 1, 0, 0);

	glTranslatef(0.0, 2, 0.0);
	glPushName(CABEZA);
	cabeza();					//CABEZA
	glPopName();
	glPushName(SOMBRERO);
	sombrero();					//SOMBRERO
	glPopName();
	glPushMatrix();
	glTranslatef(0.2, 0.1, 0.4);
	glPushName(OJO_IZQ);
	ojoi();					//OJO_IZQ
	glPopName();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.2, 0.1, 0.4);
	glPushName(OJO_DER);
	ojod();					//OJO_DER
	glPopName();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, -0.1, 0.3);
	glPushName(BOCA);
	boca();					//BOCA
	glPopName();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.0, 1.5, 0.0);
	glPushName(HOMBRO_IZQ);
	hombroi();
	glPopName();

	glRotatef(bi, 1, 0, 0);
	//BRAZO IZQUIERDO
	glRotatef(50, 1, 1, 0);
	glPushName(BRAZO_IZQ);
	brazoi();
	glPopName();
	glPopMatrix();

	glPushMatrix();

	glTranslatef(-1.0, 1.5, 0.0);
	glPushName(HOMBRO_DER);
	hombrod();
	glPopName();

	glRotatef(bd, -1, 0, 0);
	//BRAZO DERECHO
	glRotatef(-50, -1, 1, 0);
	glPushName(BRAZO_DER);
	brazod();
	glPopName();
	glPopMatrix();

	glPushMatrix();

	glTranslatef(1.0, -1.5, 0.0);
	glPushName(ART_PIERNA_IZQ);
	art_piernai();
	glPopName();

	glRotatef(pi, 1, 0, 0);
	//PIERNA IZQUIERDA
	glPushName(PIERNA_IZQ);
	piernai();
	glPopName();

	glTranslatef(0.0, -2.5, 0.3);
	glPushName(PIE_IZQ);
	piei();
	glPopName();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.0, -1.5, 0.0);
	glPushName(ART_PIERNA_DER);
	art_piernad();
	glPopName();

	glRotatef(pd, -1, 0, 0);
	//PIERNA DERECHA
	glPushName(PIERNA_DER);
	piernad();
	glPopName();

	glTranslatef(0.0, -2.5, 0.3);
	glPushName(PIE_DER);
	pied();
	glPopName();
	glPopMatrix();
}

void igvEscena3D::tronco() {
	glPushMatrix();
	if (CUERPOS) {
		GLfloat color[] = { 1.0,1.0,0.0 };
		glMaterialfv(GL_FRONT, GL_EMISSION, color);
	}
	else {
		GLfloat color[] = { 0.0,0.0,1.0 };
		glMaterialfv(GL_FRONT, GL_EMISSION, color);
	}
	glScalef(2.0, 3.0, 1.0);
	glutSolidCube(1);
	glPopMatrix();
}

void igvEscena3D::cabeza() {
	glPushMatrix();
	if (CABEZAS) {
		GLfloat color[] = { 1.0,1.0,0.0 };
		glMaterialfv(GL_FRONT, GL_EMISSION, color);
	}
	else {
		GLfloat color[] = { 1.0,0.0,1.0 };
		glMaterialfv(GL_FRONT, GL_EMISSION, color);
	}
	glutSolidSphere(0.5, 100, 100);
	glPopMatrix();
}

void igvEscena3D::sombrero() {
	glPushMatrix();
	if (SOMBREROSS) {
		GLfloat color[] = { 1.0,1.0,0.0 };
		glMaterialfv(GL_FRONT, GL_EMISSION, color);
	}
	else {
		GLfloat color[] = { 0.0,1.0,0.0 };
		glMaterialfv(GL_FRONT, GL_EMISSION, color);
	}
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(0.5, 2, 100, 100);
	glPopMatrix();
}

void igvEscena3D::ojoi() {
	glPushMatrix();
	if (OJO_IZQS) {
		GLfloat color[] = { 1.0,1.0,0.0 };
		glMaterialfv(GL_FRONT, GL_EMISSION, color);
	}
	else {
		GLfloat color[] = { 0.0,0.0,0.0 };
		glMaterialfv(GL_FRONT, GL_EMISSION, color);
	}
	glutSolidSphere(0.1, 100, 100);
	glPopMatrix();
}

void igvEscena3D::ojod() {
	glPushMatrix();
	if (OJO_DERS) {
		GLfloat color[] = { 1.0,1.0,0.0 };
		glMaterialfv(GL_FRONT, GL_EMISSION, color);
	}
	else {
		GLfloat color[] = { 0.0,0.0,0.0 };
		glMaterialfv(GL_FRONT, GL_EMISSION, color);
	}
	glutSolidSphere(0.1, 100, 100);
	glPopMatrix();
}

void igvEscena3D::boca() {
	glPushMatrix();
	if (BOCASS) {
		GLfloat color[] = { 1.0,1.0,0.0 };
		glMaterialfv(GL_FRONT, GL_EMISSION, color);
	}
	else {
		GLfloat color[] = { 0.0,1.0,1.0 };
		glMaterialfv(GL_FRONT, GL_EMISSION, color);
	}
	glRotatef(-90, 1, 0, 0);
	glutSolidTorus(0.1, 0.1, 100, 100);
	glPopMatrix();
}

void igvEscena3D::hombroi() {
	glPushMatrix();
	if (HOMBRO_IZQS) {
		GLfloat color[] = { 1.0,1.0,0.0 };
		glMaterialfv(GL_FRONT, GL_EMISSION, color);
	}
	else {
		GLfloat color[] = { 0.25,0.5,1.0 };
		glMaterialfv(GL_FRONT, GL_EMISSION, color);
	}
	glutSolidSphere(0.25, 100, 100);
	glPopMatrix();
}

void igvEscena3D::brazoi() {
	glPushMatrix();
	if (BRAZO_IZQS) {
		GLfloat color[] = { 1.0,1.0,0.0 };
		glMaterialfv(GL_FRONT, GL_EMISSION, color);
	}
	else {
		GLfloat color[] = { 1.0,0.0,1.0 };
		glMaterialfv(GL_FRONT, GL_EMISSION, color);
	}
	GLUquadricObj *br;
	br = gluNewQuadric();
	gluCylinder(br, 0.2, 0.2, 2, 100, 100);
	gluQuadricDrawStyle(br, GLU_FILL);
	glPopMatrix();
	gluDeleteQuadric(br);
}

void igvEscena3D::art_piernai() {
	glPushMatrix();
	if (ART_PIERNA_IZQS) {
		GLfloat color[] = { 1.0,1.0,0.0 };
		glMaterialfv(GL_FRONT, GL_EMISSION, color);
	}
	else {
		GLfloat color[] = { 0.25,0.5,1.0 };
		glMaterialfv(GL_FRONT, GL_EMISSION, color);
	}
	glutSolidSphere(0.25, 100, 100);
	glPopMatrix();
}

void igvEscena3D::piernai() {
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	if (PIERNA_IZQS) {
		GLfloat color[] = { 1.0,1.0,0.0 };
		glMaterialfv(GL_FRONT, GL_EMISSION, color);
	}
	else {
		GLfloat color[] = { 1.0,0.0,1.0 };
		glMaterialfv(GL_FRONT, GL_EMISSION, color);
	}
	GLUquadricObj *br;
	br = gluNewQuadric();
	gluCylinder(br, 0.2, 0.2, 2.5, 100, 100);
	gluQuadricDrawStyle(br, GLU_FILL);
	glPopMatrix();
	gluDeleteQuadric(br);
}

void igvEscena3D::piei() {
	glPushMatrix();
	if (PIE_IZQS) {
		GLfloat color[] = { 1.0,1.0,0.0 };
		glMaterialfv(GL_FRONT, GL_EMISSION, color);
	}
	else {
		GLfloat color[] = { 1.0,0.0,0.0 };
		glMaterialfv(GL_FRONT, GL_EMISSION, color);
	}
	glScalef(0.5, 0.5, 1.0);
	glutSolidCube(1);
	glPopMatrix();
}

void igvEscena3D::hombrod() {
	glPushMatrix();
	if (HOMBRO_DERS) {
		GLfloat color[] = { 1.0,1.0,0.0 };
		glMaterialfv(GL_FRONT, GL_EMISSION, color);
	}
	else {
		GLfloat color[] = { 0.25,0.5,1.0 };
		glMaterialfv(GL_FRONT, GL_EMISSION, color);
	}
	glutSolidSphere(0.25, 100, 100);
	glPopMatrix();
}

void igvEscena3D::brazod() {
	glPushMatrix();
	if (BRAZO_DERS) {
		GLfloat color[] = { 1.0,1.0,0.0 };
		glMaterialfv(GL_FRONT, GL_EMISSION, color);
	}
	else {
		GLfloat color[] = { 1.0,0.0,1.0 };
		glMaterialfv(GL_FRONT, GL_EMISSION, color);
	}
	GLUquadricObj *br;
	br = gluNewQuadric();
	gluCylinder(br, 0.2, 0.2, 2, 100, 100);
	gluQuadricDrawStyle(br, GLU_FILL);
	glPopMatrix();
	gluDeleteQuadric(br);
}

void igvEscena3D::art_piernad() {
	glPushMatrix();
	if (ART_PIERNA_DERS) {
		GLfloat color[] = { 1.0,1.0,0.0 };
		glMaterialfv(GL_FRONT, GL_EMISSION, color);
	}
	else {
		GLfloat color[] = { 0.25,0.5,1.0 };
		glMaterialfv(GL_FRONT, GL_EMISSION, color);
	}
	glutSolidSphere(0.25, 100, 100);
	glPopMatrix();
}

void igvEscena3D::piernad() {
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	if (PIERNA_DERS) {
		GLfloat color[] = { 1.0,1.0,0.0 };
		glMaterialfv(GL_FRONT, GL_EMISSION, color);
	}
	else {
		GLfloat color[] = { 1.0,0.0,1.0 };
		glMaterialfv(GL_FRONT, GL_EMISSION, color);
	}
	GLUquadricObj *br;
	br = gluNewQuadric();
	gluCylinder(br, 0.2, 0.2, 2.5, 100, 100);
	gluQuadricDrawStyle(br, GLU_FILL);
	glPopMatrix();
	gluDeleteQuadric(br);
}

void igvEscena3D::pied() {
	glPushMatrix();
	if (PIE_DERS) {
		GLfloat color[] = { 1.0,1.0,0.0 };
		glMaterialfv(GL_FRONT, GL_EMISSION, color);
	}
	else {
		GLfloat color[] = { 1.0,0.0,0.0 };
		glMaterialfv(GL_FRONT, GL_EMISSION, color);
	}
	glScalef(0.5, 0.5, 1.0);
	glutSolidCube(1);
	glPopMatrix();
}