#ifndef __IGVESCENA3D
#define __IGVESCENA3D

#include <glut.h>

#include <iostream>
#include "TAPLinearInterpolation.h"
using namespace std;

class igvEscena3D {
	Puntos movimiento;
	protected:
	// añadir quí los atributos para el control de los grados de libertad del modelo

		GLfloat cuerpo;
		GLfloat rcabeza;
		GLfloat rcabeza2;
		GLfloat bi;
		GLfloat bd;
		GLfloat pi;
		GLfloat pd;

////// Apartado D: añadir aquí el atributo/s para el control del objeto seleccionado y colorearlo en amarillo

		GLint CUERPO;
		GLint CABEZA;
		GLint OJO_IZQ;
		GLint OJO_DER;
		GLint BOCA;
		GLint SOMBRERO;
		GLint HOMBRO_IZQ;
		GLint HOMBRO_DER;
		GLint BRAZO_IZQ;
		GLint BRAZO_DER;
		GLint ART_PIERNA_IZQ;
		GLint ART_PIERNA_DER;
		GLint PIERNA_IZQ;
		GLint PIERNA_DER;
		GLint PIE_IZQ;
		GLint PIE_DER;

		bool CUERPOS;
		bool CABEZAS;
		bool OJO_IZQS;
		bool OJO_DERS;
		bool BOCASS;
		bool SOMBREROSS;
		bool HOMBRO_IZQS;
		bool HOMBRO_DERS;
		bool BRAZO_IZQS;
		bool BRAZO_DERS;
		bool ART_PIERNA_IZQS;
		bool ART_PIERNA_DERS;
		bool PIERNA_IZQS;
		bool PIERNA_DERS;
		bool PIE_IZQS;
		bool PIE_DERS;


		// Otros atributos		
		bool ejes;

	public:
		// Constructores por defecto y destructor
		igvEscena3D();
		~igvEscena3D();

		// Metodos estáticos

		// Métodos
		// método con las llamadas OpenGL para visualizar la escena
    void visualizar(void);
	void pintarGrafo(void);
	void tronco(void);
	void cabeza(void);
	void sombrero(void);
	void ojoi(void);
	void ojod(void);
	void boca(void);
	void hombroi(void);
	void brazoi(void);
	void art_piernai(void);
	void piernai(void);
	void piei(void);
	void hombrod(void);
	void brazod(void);
	void art_piernad(void);
	void piernad(void);
	void pied(void);

	void setMovimiento(Puntos _mov) {
		movimiento.x = _mov.x;
		movimiento.y = _mov.y;
		movimiento.z = _mov.z;
	}


////// Apartado B: añadir aquí los métodos para modificar los grados de libertad del modelo

	void rotarCuerpo(GLfloat rotacion){cuerpo+=rotacion;};

	void rotarCabezaY(GLfloat rotacion){
		if(rcabeza+rotacion<=45 && rcabeza+rotacion>=-45)rcabeza+=rotacion;
	}

	void rotarCabezaX(GLfloat rotacion){
		if(rcabeza2+rotacion<=5 && rcabeza2+rotacion>=-4)rcabeza2+=rotacion;
	}

	void rotarBrazoIzq(GLfloat rotacion){
		if(bi+rotacion<=100 && bi+rotacion>=-10)bi+=rotacion;
	}

	void rotarBrazoDer(GLfloat rotacion){
		if(bd+rotacion<=10 && bd+rotacion>=-100)bd+=rotacion;
	}

	void rotarPiernaIzq(GLfloat rotacion){
		if(pi+rotacion<=50 && pi+rotacion>=-50)pi+=rotacion;
	}

	void rotarPiernaDer(GLfloat rotacion){
		if(pd+rotacion<=50 && pd+rotacion>=-50)pd+=rotacion;
	}

	// añadir aquí el método/s para indicar el objeto seleccionado

	void obejetoSelecionado(int _objetoSelecionado){
		if(_objetoSelecionado==CUERPO)CUERPOS=true;
		else CUERPOS=false;
		if(_objetoSelecionado==CABEZA)CABEZAS=true;
		else CABEZAS=false;
		if(_objetoSelecionado==OJO_IZQ)OJO_IZQS=true;
		else OJO_IZQS=false;
		if(_objetoSelecionado==OJO_DER)OJO_DERS=true;
		else OJO_DERS=false;
		if(_objetoSelecionado==BOCA)BOCASS=true;
		else BOCASS=false;
		if(_objetoSelecionado==SOMBRERO)SOMBREROSS=true;
		else SOMBREROSS=false;
		if(_objetoSelecionado==HOMBRO_IZQ)HOMBRO_IZQS=true;
		else HOMBRO_IZQS=false;
		if(_objetoSelecionado==HOMBRO_DER)HOMBRO_DERS=true;
		else HOMBRO_DERS=false;
		if(_objetoSelecionado==BRAZO_IZQ)BRAZO_IZQS=true;
		else BRAZO_IZQS=false;
		if(_objetoSelecionado==BRAZO_DER)BRAZO_DERS=true;
		else BRAZO_DERS=false;
		if(_objetoSelecionado==ART_PIERNA_IZQ)ART_PIERNA_IZQS=true;
		else ART_PIERNA_IZQS=false;
		if(_objetoSelecionado==ART_PIERNA_DER)ART_PIERNA_DERS=true;
		else ART_PIERNA_DERS=false;
		if(_objetoSelecionado==PIERNA_IZQ)PIERNA_IZQS=true;
		else PIERNA_IZQS=false;
		if(_objetoSelecionado==PIERNA_DER)PIERNA_DERS=true;
		else PIERNA_DERS=false;
		if(_objetoSelecionado==PIE_IZQ)PIE_IZQS=true;
		else PIE_IZQS=false;
		if(_objetoSelecionado==PIE_DER)PIE_DERS=true;
		else PIE_DERS=false;
		cout << _objetoSelecionado << "\n";
}

		bool get_ejes() {return ejes;};
		void set_ejes(bool _ejes){ejes = _ejes;};
};

#endif
