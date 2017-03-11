#include "TAPMotionController.h"

#define Epsilon 0.000001

static bool iguales(float a, float b) {
	return (abs(a - b) <= Epsilon);
}

/**
* Constructor parametrizado
*/
TAPMotionController::TAPMotionController(){
	nEntradasTabla = 0;
}

/**
* Constructor parametrizado
*/
TAPMotionController::TAPMotionController(int n, TAPBezier _desp, TAPSpeedController _vel){
	nEntradasTabla = n;

	desplazamiento = TAPBezier(_desp);
	velocidad = TAPSpeedController(_vel);

	construirTablaIncrementos();
}

/**
* COnstructor de copia
*/
TAPMotionController::TAPMotionController(const TAPMotionController & motioncontroller){
	nEntradasTabla = motioncontroller.nEntradasTabla;

	desplazamiento = TAPBezier(motioncontroller.desplazamiento);
	velocidad = TAPSpeedController(motioncontroller.velocidad);

	construirTablaIncrementos();
}

/**
* Funcion que construye la tabla de incrementos con la cual podemos
* obtener el valor u dada un desplazamiento s, y asi poder calcular
* posteriormente la poscion p en el instante t
*/
void TAPMotionController::construirTablaIncrementos(){
	tablaIncrementos.clear();
	
	float incremento = 1.0f / (float)nEntradasTabla;

	float despl_Acumulado = 0.0f;
	float uAcumulada = 0.0f;
	int i = 0;

	tablaIncrementos.insert(std::pair<float, int>(despl_Acumulado, i));

	while (uAcumulada < 1.0f || iguales(uAcumulada, 1.0f)) {

	}
}

/**
* Funcion que devuelve el Punto p en el que el objete se encuentre
* en el instante t
*/
Punto TAPMotionController::get_Punto(float t)
{
	return Punto();
}

/**
* Destructor
*/
TAPMotionController::~TAPMotionController(){}
