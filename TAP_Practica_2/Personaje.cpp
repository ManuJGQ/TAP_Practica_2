#include <cstdlib>
#include <stdio.h>
#include "Personaje.h"

Personaje::Personaje(void){
	SELECIONADO=false;
}


Personaje::~Personaje(void){}

void Personaje::visualizar() {
	// crear el modelo
	glPushMatrix(); // guarda la matriz de modelado

	igvFuenteLuz luzf(GL_LIGHT2,igvPunto3D(0,50,0),igvColor(0.0,0.0,0.0,0.0),igvColor(1.0,1.0,1.0,1.0),igvColor(1.0,1.0,1.0,1.0),1.0,0.0,0.0,igvPunto3D(0,-50,0),12.0,50);
	luzf.aplicar();
	 pintarGrafo();

	glPopMatrix (); // restaura la matriz de modelado
}

void Personaje::pintarGrafo(){
	glRotatef(0,0,1,0);
	tronco();						//CUERPO
	glPushMatrix();						//CABEZA COMPLETA

		glRotatef(0,0,1,0);
		glRotatef(0,1,0,0);

		glTranslatef(0.0,2,0.0);
		cabeza();					//CABEZA
		sombrero();					//SOMBRERO
		glPushMatrix();
			glTranslatef(0.2,0.1,0.4);
			ojoi();					//OJO_IZQ
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-0.2,0.1,0.4);
			ojod();					//OJO_DER
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.0,-0.1,0.3);
			boca();					//BOCA
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(1.0,1.5,0.0);
		hombroi();

		glRotatef(0,1,0,0);
													//BRAZO IZQUIERDO
		glRotatef(80,1,1,0);
		brazoi();
	glPopMatrix();

	glPushMatrix();

		glTranslatef(-1.0,1.5,0.0);
		hombrod();

		glRotatef(0,-1,0,0);
													//BRAZO DERECHO
		glRotatef(-80,-1,1,0);
		brazod();
	glPopMatrix();

	glPushMatrix();

		glTranslatef(1.0,-1.5,0.0);
		art_piernai();

		glRotatef(0,1,0,0);
													//PIERNA IZQUIERDA									
		piernai();

		glTranslatef(0.0,-2.5,0.3);
		piei();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-1.0,-1.5,0.0);
		art_piernad();

		glRotatef(0,-1,0,0);
													//PIERNA DERECHA										
		piernad();

		glTranslatef(0.0,-2.5,0.3);
		pied();
	glPopMatrix();
}

void Personaje::tronco(){
	glPushMatrix();
		if(SELECIONADO){
			GLfloat color[]={1.0,1.0,0.0};
			glMaterialfv(GL_FRONT,GL_EMISSION,color);
		}else{
			GLfloat color[]={0.0,0.0,1.0};
			glMaterialfv(GL_FRONT,GL_EMISSION,color);
		}
		glScalef(2.0,3.0,1.0);
		glutSolidCube(1);
	glPopMatrix();
}

void Personaje::cabeza(){
	glPushMatrix();
		if(SELECIONADO){
			GLfloat color[]={1.0,1.0,0.0};
			glMaterialfv(GL_FRONT,GL_EMISSION,color);
		}else{
			GLfloat color[]={1.0,0.0,1.0};
			glMaterialfv(GL_FRONT,GL_EMISSION,color);
		}
		glutSolidSphere(0.5,100,100);
	glPopMatrix();
}

void Personaje::sombrero(){
	glPushMatrix();
		if(SELECIONADO){
			GLfloat color[]={1.0,1.0,0.0};
			glMaterialfv(GL_FRONT,GL_EMISSION,color);
		}else{
			GLfloat color[]={0.0,1.0,0.0};
			glMaterialfv(GL_FRONT,GL_EMISSION,color);
		}
		glRotatef(-90,1,0,0);
		glutSolidCone(0.5, 2, 100, 100);
	glPopMatrix();
}

void Personaje::ojoi(){
	glPushMatrix();
		if(SELECIONADO){
			GLfloat color[]={1.0,1.0,0.0};
			glMaterialfv(GL_FRONT,GL_EMISSION,color);
		}else{
			GLfloat color[]={0.0,0.0,0.0};
			glMaterialfv(GL_FRONT,GL_EMISSION,color);
		}
		glutSolidSphere(0.1,100,100);
	glPopMatrix();
}

void Personaje::ojod(){
	glPushMatrix();
		if(SELECIONADO){
			GLfloat color[]={1.0,1.0,0.0};
			glMaterialfv(GL_FRONT,GL_EMISSION,color);
		}else{
			GLfloat color[]={0.0,0.0,0.0};
			glMaterialfv(GL_FRONT,GL_EMISSION,color);
		}
		glutSolidSphere(0.1,100,100);
	glPopMatrix();
}

void Personaje::boca(){
	glPushMatrix();
		if(SELECIONADO){
			GLfloat color[]={1.0,1.0,0.0};
			glMaterialfv(GL_FRONT,GL_EMISSION,color);
		}else{
			GLfloat color[]={0.0,1.0,1.0};
		glMaterialfv(GL_FRONT,GL_EMISSION,color);
		}	
		glRotatef(-90,1,0,0);
		glutSolidTorus(0.1, 0.1, 100, 100);
	glPopMatrix();
}

void Personaje::hombroi(){
	glPushMatrix();
		if(SELECIONADO){
			GLfloat color[]={1.0,1.0,0.0};
			glMaterialfv(GL_FRONT,GL_EMISSION,color);
		}else{
			GLfloat color[]={0.25,0.5,1.0};
			glMaterialfv(GL_FRONT,GL_EMISSION,color);
		}	
		glutSolidSphere(0.25,100,100);
	glPopMatrix();
}

void Personaje::brazoi(){
	glPushMatrix();
		if(SELECIONADO){
			GLfloat color[]={1.0,1.0,0.0};
			glMaterialfv(GL_FRONT,GL_EMISSION,color);
		}else{
			GLfloat color[]={1.0,0.0,1.0};
			glMaterialfv(GL_FRONT,GL_EMISSION,color);
		}	
		GLUquadricObj *br;
		br=gluNewQuadric();
		gluCylinder(br,0.2,0.2,2,100,100);
		gluQuadricDrawStyle(br,GLU_FILL);
	glPopMatrix();
	gluDeleteQuadric(br);
}

void Personaje::art_piernai(){
	glPushMatrix();
		if(SELECIONADO){
			GLfloat color[]={1.0,1.0,0.0};
			glMaterialfv(GL_FRONT,GL_EMISSION,color);
		}else{
			GLfloat color[]={0.25,0.5,1.0};
			glMaterialfv(GL_FRONT,GL_EMISSION,color);
		}
		glutSolidSphere(0.25,100,100);
	glPopMatrix();
}

void Personaje::piernai(){
	glPushMatrix();
		glRotatef(90,1,0,0);
		if(SELECIONADO){
			GLfloat color[]={1.0,1.0,0.0};
			glMaterialfv(GL_FRONT,GL_EMISSION,color);
		}else{
			GLfloat color[]={1.0,0.0,1.0};
			glMaterialfv(GL_FRONT,GL_EMISSION,color);
		}
		GLUquadricObj *br;
		br=gluNewQuadric();
		gluCylinder(br,0.2,0.2,2.5,100,100);
		gluQuadricDrawStyle(br,GLU_FILL);
	glPopMatrix();
	gluDeleteQuadric(br);
}

void Personaje::piei(){
	glPushMatrix();
		if(SELECIONADO){
			GLfloat color[]={1.0,1.0,0.0};
			glMaterialfv(GL_FRONT,GL_EMISSION,color);
		}else{
			GLfloat color[]={1.0,0.0,0.0};
			glMaterialfv(GL_FRONT,GL_EMISSION,color);
		}
		glScalef(0.5,0.5,1.0);
		glutSolidCube(1);
	glPopMatrix();
}

void Personaje::hombrod(){
	glPushMatrix();
		if(SELECIONADO){
			GLfloat color[]={1.0,1.0,0.0};
			glMaterialfv(GL_FRONT,GL_EMISSION,color);
		}else{
			GLfloat color[]={0.25,0.5,1.0};
			glMaterialfv(GL_FRONT,GL_EMISSION,color);
		}	
		glutSolidSphere(0.25,100,100);
	glPopMatrix();
}

void Personaje::brazod(){
	glPushMatrix();
		if(SELECIONADO){
			GLfloat color[]={1.0,1.0,0.0};
			glMaterialfv(GL_FRONT,GL_EMISSION,color);
		}else{
			GLfloat color[]={1.0,0.0,1.0};
			glMaterialfv(GL_FRONT,GL_EMISSION,color);
		}	
		GLUquadricObj *br;
		br=gluNewQuadric();
		gluCylinder(br,0.2,0.2,2,100,100);
		gluQuadricDrawStyle(br,GLU_FILL);
	glPopMatrix();
	gluDeleteQuadric(br);
}

void Personaje::art_piernad(){
	glPushMatrix();
		if(SELECIONADO){
			GLfloat color[]={1.0,1.0,0.0};
			glMaterialfv(GL_FRONT,GL_EMISSION,color);
		}else{
			GLfloat color[]={0.25,0.5,1.0};
			glMaterialfv(GL_FRONT,GL_EMISSION,color);
		}
		glutSolidSphere(0.25,100,100);
	glPopMatrix();
}

void Personaje::piernad(){
	glPushMatrix();
		glRotatef(90,1,0,0);
		if(SELECIONADO){
			GLfloat color[]={1.0,1.0,0.0};
			glMaterialfv(GL_FRONT,GL_EMISSION,color);
		}else{
			GLfloat color[]={1.0,0.0,1.0};
			glMaterialfv(GL_FRONT,GL_EMISSION,color);
		}
		GLUquadricObj *br;
		br=gluNewQuadric();
		gluCylinder(br,0.2,0.2,2.5,100,100);
		gluQuadricDrawStyle(br,GLU_FILL);
	glPopMatrix();
	gluDeleteQuadric(br);
}

void Personaje::pied(){
	glPushMatrix();
		if(SELECIONADO){
			GLfloat color[]={1.0,1.0,0.0};
			glMaterialfv(GL_FRONT,GL_EMISSION,color);
		}else{
			GLfloat color[]={1.0,0.0,0.0};
			glMaterialfv(GL_FRONT,GL_EMISSION,color);
		}
		glScalef(0.5,0.5,1.0);
		glutSolidCube(1);
	glPopMatrix();
}