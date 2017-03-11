#include <cstdlib>
#include <stdio.h>

#include <glui.h>

#include "igvInterfaz.h"

extern igvInterfaz interfaz; // los callbacks deben ser estaticos y se requiere este objeto para acceder desde
							 // ellos a las variables de la clase

// Metodos constructores -----------------------------------

igvInterfaz::igvInterfaz() {
	//inicialización de los atributos para realizar la selección mediante lista de impactos
	modo = IGV_VISUALIZAR;

	ang = 70;

	va.set(0, 1.0, 0);

	i = 0;
	vistas[0].set(6.0, 4.0, 8);
	vistas[1].set(10, 0, 0);
	vistas[2].set(0, 10, 0);
	vistas[3].set(0, 0, 10);

	planos[1] = -3;
	planos[2] = 1;

	formato = false;
	vista = false;

	animacion = false;

	linearInterpolation = TAPLinearInterpolation("linearInterpolation.txt");
	pt = linearInterpolation.getPrimeraT();
	ut = linearInterpolation.getUltimoT();
	puntoActual = linearInterpolation.getPosicionInterpolada(pt);

	sphericalInterpolation = TAPSphericalInterpolation("sphericalInterpolation.txt");
	spt = sphericalInterpolation.getPrimeraT();
	sut = sphericalInterpolation.getUltimoT();

	travelling = 0;

	bezier = TAPBezier({ 0.0f, 2.0f, 0.0f }, { 3.0f, -2.0f, 0.0f }, { 5.0f, 20.0f, 0.0f }, { 3.0f, 4.0f, 0.0f });
}

igvInterfaz::~igvInterfaz() {}


// Metodos publicos ----------------------------------------

void igvInterfaz::crear_mundo(void) {
	//// Apartado B: establecer los parámetros de la cámara en función de la escena concreta que se esté modelando
	interfaz.camara.set(IGV_PARALELA, interfaz.get_vistas(interfaz.i), igvPunto3D(0, 0, 0), interfaz.get_va(),
		-1 * 5, 1 * 5, -1 * 5, 1 * 5, interfaz.planos[1], 200);
}

void igvInterfaz::configura_entorno(int argc, char** argv,
	int _ancho_ventana, int _alto_ventana,
	int _pos_X, int _pos_Y, string _titulo) {

	// inicialización de las variables de la interfaz																	
	ancho_ventana = _ancho_ventana;
	alto_ventana = _alto_ventana;

	// inicialización de la ventana de visualización
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(_ancho_ventana, _alto_ventana);
	glutInitWindowPosition(_pos_X, _pos_Y);
	glutCreateWindow(_titulo.c_str());

	//float version = GLUI_Master.get_version();
	//GLUI *glui_window = GLUI_Master.create_glui("GLUI");
	////glui_window->add_button("Hello World!");

	glEnable(GL_DEPTH_TEST); // activa el ocultamiento de superficies por z-buffer
	glClearColor(1.0, 1.0, 1.0, 0.0); // establece el color de fondo de la ventana

	glEnable(GL_LIGHTING); // activa la iluminacion de la escena
	glEnable(GL_NORMALIZE); // normaliza los vectores normales para calculo iluminacion

	crear_mundo(); // crea el mundo a visualizar en la ventana
}

void igvInterfaz::inicia_bucle_visualizacion() {
	glutMainLoop(); // inicia el bucle de visualizacion de OpenGL
}

void igvInterfaz::set_glutKeyboardFunc(unsigned char key, int x, int y) {
	switch (key) {
		// incluir aquí el cambio de la cámara para mostrar las vistas planta, perfil, alzado o perspectiva
	case 'V':
	case 'v':
		interfaz.i++;
		interfaz.vistas[3].set(0, 0, 10);
		if (interfaz.i > 3)interfaz.i = 0;
		if (interfaz.i == 2)interfaz.set_va(1.0, 0, 0);
		else interfaz.set_va(0, 1.0, 0);
		interfaz.camara.set(interfaz.get_vistas(interfaz.i), igvPunto3D(0, 0, 0), interfaz.get_va());
		interfaz.camara.aplicar();
		break;
	case 't':
		interfaz.escena.setTwist(0.01);
		break;
	case 'T':
		interfaz.escena.setTwist(-0.01);
		break;
	case 'R':
	case 'r':
		interfaz.escena.setTapering(interfaz.escena.getTapering() ? false : true);
		break;
	case 'A':
	case 'a': // activa/desactiva la animación de la escena
	// incluir aquí la activación de la animación
		interfaz.animacion = (interfaz.animacion ? false : true);
		break;
	case 'e': // activa/desactiva la visualizacion de los ejes
		interfaz.escena.set_ejes(interfaz.escena.get_ejes() ? false : true);
		break;
	case '+':
		interfaz.camara.zoom(5);
		break;
	case '-':
		interfaz.camara.zoom(-5);
		break;
	case 27: // tecla de escape para SALIR
		exit(1);
		break;
	}
	glutPostRedisplay(); // renueva el contenido de la ventana de vision
}

void igvInterfaz::SpecialInput(int key, int x, int y) {
	switch (key){
	case GLUT_KEY_LEFT:
		interfaz.i = 0;
		interfaz.travelling--;
		interfaz.vistas[0].set(0.0 + interfaz.travelling, 4.0, 15.0);
		interfaz.camara.set(interfaz.get_vistas(interfaz.i), igvPunto3D(interfaz.travelling, 0, 0), interfaz.get_va());
		interfaz.camara.aplicar();
		break;
	case GLUT_KEY_RIGHT:
		interfaz.i = 0;
		interfaz.travelling++;
		interfaz.vistas[0].set(0.0 + interfaz.travelling, 4.0, 15.0);
		interfaz.camara.set(interfaz.get_vistas(interfaz.i), igvPunto3D(interfaz.travelling, 0, 0), interfaz.get_va());
		interfaz.camara.aplicar();
		break;
	}
	glutPostRedisplay(); // renueva el contenido de la ventana de vision
}

void igvInterfaz::set_glutReshapeFunc(int w, int h) {
	// dimensiona el viewport al nuevo ancho y alto de la ventana
	// guardamos valores nuevos de la ventana de visualizacion
	interfaz.set_ancho_ventana(w);
	interfaz.set_alto_ventana(h);

	// establece los parámetros de la cámara y de la proyección
	interfaz.camara.aplicar();
}

void igvInterfaz::set_glutDisplayFunc() {
	GLuint lista_impactos[1024]; // array con la lista de impactos cuando se visualiza en modo selección

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // borra la ventana y el z-buffer

	// se establece el viewport
	glViewport(0, 0, interfaz.get_ancho_ventana(), interfaz.get_alto_ventana());


	// aplica las transformaciones en función de los parámetros de la cámara y del modo (visualización o selección)
	interfaz.camara.aplicar();

	interfaz.bezier.pintarCurva();

	// visualiza la escena
	interfaz.escena.visualizar();


	// refresca la ventana
	glutSwapBuffers();

}


void igvInterfaz::set_glutIdleFunc() {
	// incluir el código para animar el modelo de la manera más realista posible
	if (interfaz.animacion) {
		/***************************************************************
		*					INTERPOLACION LINEAL					   *
		***************************************************************/
		interfaz.pt += 0.01;
		if (interfaz.pt > interfaz.ut) {
			interfaz.pt = interfaz.linearInterpolation.getPrimeraT();
		}
		Puntos nuevoPunto = interfaz.linearInterpolation.getPosicionInterpolada(interfaz.pt);

		Puntos movimiento;
		movimiento.x = nuevoPunto.x - interfaz.puntoActual.x;
		movimiento.y = nuevoPunto.y - interfaz.puntoActual.y;
		movimiento.z = nuevoPunto.z - interfaz.puntoActual.z;

		/*std::cout << "--------------------------------------------------------" << std::endl;
		std::cout << interfaz.puntoActual.x << " " << interfaz.puntoActual.y << " " << interfaz.puntoActual.z << std::endl;*/

		interfaz.puntoActual = nuevoPunto;

		//std::cout << nuevoPunto.x << " " << nuevoPunto.y << " " << nuevoPunto.z << std::endl;
		//std::cout << movimiento.x << " " << movimiento.y << " " << movimiento.z << std::endl;

		interfaz.escena.setMovimiento(nuevoPunto);

		/***************************************************************
		*					INTERPOLACION ESFERICA					   *
		***************************************************************/
		interfaz.spt += 0.01;
		if (interfaz.spt > interfaz.sut) {
			interfaz.spt = interfaz.sphericalInterpolation.getPrimeraT();
		}
		Quaternion nuevoGiro = interfaz.sphericalInterpolation.getPosicionInterpolada(interfaz.spt);

		interfaz.escena.setGiro(nuevoGiro);

		glutPostRedisplay();
	}
}

void igvInterfaz::inicializa_callbacks() {
	glutKeyboardFunc(set_glutKeyboardFunc);
	glutReshapeFunc(set_glutReshapeFunc);
	glutDisplayFunc(set_glutDisplayFunc);
	glutIdleFunc(set_glutIdleFunc);
	glutSpecialFunc(SpecialInput);
}
