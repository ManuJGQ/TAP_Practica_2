#ifndef __PERSONAJE
#define __PERSONAJE

#include <glut.h>

#include "igvFuenteLuz.h"
#include "igvMaterial.h"
#include <iostream>
using namespace std;

class Personaje{
public:
	Personaje(void);
	~Personaje(void);

	bool SELECIONADO;

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
};

#endif
