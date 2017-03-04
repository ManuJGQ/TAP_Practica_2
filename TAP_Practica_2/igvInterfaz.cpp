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
	objeto_seleccionado = -1;
	boton_retenido = false;

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

	pierna = 0;
	brazo = 0;
	cabezaS = 0;
	cabezaN = 0;

	bpierna = true;
	bbrazo = true;
	bcabezaS = true;
	bcabezaN = true;

	linearInterpolation = TAPLinearInterpolation("linearInterpolation.txt");
	pt = linearInterpolation.getPrimeraT();
	ut = linearInterpolation.getUltimoT();
	puntoActual = linearInterpolation.getPosicionInterpolada(pt);

	sphericalInterpolation = TAPSphericalInterpolation("sphericalInterpolation.txt");
	spt = sphericalInterpolation.getPrimeraT();
	sut = sphericalInterpolation.getUltimoT();

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
	case 'v':
		interfaz.i++;
		if (interfaz.i > 3)interfaz.i = 0;
		if (interfaz.i == 2)interfaz.set_va(1.0, 0, 0);
		else interfaz.set_va(0, 1.0, 0);
		interfaz.camara.set(interfaz.get_vistas(interfaz.i), igvPunto3D(0, 0, 0), interfaz.get_va());
		interfaz.camara.aplicar();
		break;
		//incluir aquí la modificación de los grados de libertad del modelo pulsando las teclas correspondientes
	case 'c':
		interfaz.escena.rotarCuerpo(5);
		break;
	case 'C':
		interfaz.escena.rotarCuerpo(-5);
		break;
	case 'n':
		interfaz.escena.rotarCabezaY(5);
		break;
	case 'N':
		interfaz.escena.rotarCabezaY(-5);
		break;
	case 's':
		interfaz.escena.rotarCabezaX(1);
		break;
	case 'S':
		interfaz.escena.rotarCabezaX(-1);
		break;
	case 'i':
		interfaz.escena.rotarBrazoIzq(5);
		break;
	case 'I':
		interfaz.escena.rotarBrazoIzq(-5);
		break;
	case 'd':
		interfaz.escena.rotarBrazoDer(-5);
		break;
	case 'D':
		interfaz.escena.rotarBrazoDer(5);
		break;
	case 'l':
		interfaz.escena.rotarPiernaIzq(5);
		break;
	case 'L':
		interfaz.escena.rotarPiernaIzq(-5);
		break;
	case 'r':
		interfaz.escena.rotarPiernaDer(-5);
		break;
	case 'R':
		interfaz.escena.rotarPiernaDer(5);
		break;
	case 't':
		interfaz.escena.setTwist(0.01);
		break;
	case 'T':
		interfaz.escena.rotarPiernaDer(5);
		break;
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

	// antes de aplicar las transformaciones de cámara y proyección hay comprobar el modo,
	if (interfaz.modo == IGV_SELECCIONAR) {
		// si se está seleccionando se pasa a modo selección de OpenGL y se pasan los parámetros de selección a la cámara
		interfaz.inicia_seleccion(1024, lista_impactos);
	}

	// aplica las transformaciones en función de los parámetros de la cámara y del modo (visualización o selección)
	interfaz.camara.aplicar();

	// visualiza la escena
	interfaz.escena.visualizar();

	if (interfaz.modo == IGV_SELECCIONAR) {
		// salir del modo seleccion y procesar la lista de impactos
		interfaz.finaliza_seleccion(1024, lista_impactos);
	}
	else {
		// refresca la ventana
		glutSwapBuffers();
	}
}

void igvInterfaz::set_glutMouseFunc(GLint boton, GLint estado, GLint x, GLint y) {

	// comprobar que se ha pulsado el botón izquierdo 

	if (boton == 0) {

		// guardar que el boton se ha presionado o se ha soltado, si se ha pulsado hay que
		// pasar a modo IGV_SELECCIONAR

		if (estado = GLUT_UP)interfaz.boton_retenido = true;
		else interfaz.boton_retenido = false;
		if (interfaz.boton_retenido)interfaz.modo = IGV_SELECCIONAR;
		else interfaz.modo = IGV_VISUALIZAR;

		// guardar el pixel pulsado

		interfaz.cursorX = x;
		interfaz.cursorY = y;

		// renovar el contenido de la ventana de vision 

		glutPostRedisplay();
	}

}

void igvInterfaz::set_glutMotionFunc(GLint x, GLint y) {

	// si el botón está retenido y hay algún objeto seleccionado,
	// comprobar el objeto seleccionado y la posición del ratón y actualizar
	// convenientemente el grado de libertad del objeto correspondiente 

	if (interfaz.boton_retenido && interfaz.get_objeto_seleccionado() != -1) {
		if (interfaz.get_objeto_seleccionado() == 1)interfaz.escena.rotarCuerpo(((interfaz.cursorX - x))*-0.05);
		//if (interfaz.get_objeto_seleccionado() == 2)interfaz.escena.rotarCabezaY(((interfaz.cursorX - x))*-1);
		//if (interfaz.get_objeto_seleccionado() == 2)interfaz.escena.rotarCabezaX(((interfaz.cursorY - y))*-0.5);
		//if (interfaz.get_objeto_seleccionado() == 9)interfaz.escena.rotarBrazoIzq(((interfaz.cursorX - x))*-1.5);
		//if (interfaz.get_objeto_seleccionado() == 10)interfaz.escena.rotarBrazoDer(((interfaz.cursorX - x))*1.5);
		//if (interfaz.get_objeto_seleccionado() == 13)interfaz.escena.rotarPiernaIzq(((interfaz.cursorX - x))*-1.5);
		//if (interfaz.get_objeto_seleccionado() == 14)interfaz.escena.rotarPiernaDer(((interfaz.cursorX - x))*1.5);

		// guardar la nueva posición del ratón 

		interfaz.cursorX = x;
		interfaz.cursorY = y;

		// renovar el contenido de la ventana de vision 

		glutPostRedisplay();
	}

}

void igvInterfaz::set_glutIdleFunc() {
	// incluir el código para animar el modelo de la manera más realista posible
	if (interfaz.animacion) {
		if (interfaz.bcabezaS) {
			if (interfaz.cabezaS + 1 > 10)interfaz.bcabezaS = false;
		}
		else {
			if (interfaz.cabezaS - 1 < -8)interfaz.bcabezaS = true;
		}
		if (interfaz.bcabezaN) {
			if (interfaz.cabezaN + 1 > 45)interfaz.bcabezaN = false;
		}
		else {
			if (interfaz.cabezaN - 1 < -45)interfaz.bcabezaN = true;
		}
		if (interfaz.bbrazo) {
			if (interfaz.brazo + 1 > 33)interfaz.bbrazo = false;
		}
		else {
			if (interfaz.brazo - 1 < -5)interfaz.bbrazo = true;
		}
		if (interfaz.bpierna) {
			if (interfaz.pierna + 1 > 17)interfaz.bpierna = false;
		}
		else {
			if (interfaz.pierna - 1 < -17)interfaz.bpierna = true;
		}
		if (interfaz.bcabezaN) {
			interfaz.escena.rotarCabezaY(1);
			interfaz.cabezaN++;
		}
		else {
			interfaz.escena.rotarCabezaY(-1);
			interfaz.cabezaN--;
		}
		if (interfaz.bcabezaS) {
			interfaz.escena.rotarCabezaX(0.5);
			interfaz.cabezaS++;
		}
		else {
			interfaz.escena.rotarCabezaX(-0.5);
			interfaz.cabezaS--;
		}
		if (interfaz.bbrazo) {
			interfaz.escena.rotarBrazoIzq(3);
			interfaz.escena.rotarBrazoDer(3);
			interfaz.brazo++;
		}
		else {
			interfaz.escena.rotarBrazoIzq(-3);
			interfaz.escena.rotarBrazoDer(-3);
			interfaz.brazo--;
		}
		if (interfaz.bpierna) {
			interfaz.escena.rotarPiernaIzq(3);
			interfaz.escena.rotarPiernaDer(3);
			interfaz.pierna++;
		}
		else {
			interfaz.escena.rotarPiernaIzq(-3);
			interfaz.escena.rotarPiernaDer(-3);
			interfaz.pierna--;
		}

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

	glutMouseFunc(set_glutMouseFunc);
	glutMotionFunc(set_glutMotionFunc);
	glutIdleFunc(set_glutIdleFunc);
}

void igvInterfaz::inicia_seleccion(int TAMANO_LISTA_IMPACTOS, GLuint *lista_impactos) {
	// establecer dónde se van a almacenar los impactos

	glSelectBuffer(TAMANO_LISTA_IMPACTOS, lista_impactos);

	// pasar a modo de seleccion de OpenGL

	glRenderMode(GL_SELECT);

	// establecer la camara en modo seleccion con los parámetros necesarios para realizar la selección
	// para el alto y el ancho de la ventana de selección probar diferentes tamaños y comprobar la amplitud de la selección

	interfaz.camara.establecerSeleccion(2, 2, cursorX, cursorY);

}

int procesar_impactos(int numero_impactos, GLuint *lista_impactos) {
	/* esta función debe devolver el código del objeto seleccionado, que no tiene porque coincidir con el nombre
	   asignado con la pila de nombres, y si se han utilizado nombres jerárquicos hay que tener en cuenta que
		 esta función sólo devolver un único código */

		 // recorrer la lista de impactos con numero_impactos impactos,
		 // guardar el más próximo al observador (minima Z)
		 // para empezar, considerar que la mínima Z tiene un valor de 0xffffffff (el tope del tipo GLuint)

	if (numero_impactos == 0) {
		interfaz.set_objeto_seleccionado(-1);
		return -1;
	}
	unsigned int minimaZ = 0xffffffff;
	int j = 0;
	for (int i = 0; i < numero_impactos; i++) {
		int despl = lista_impactos[j];
		if (lista_impactos[j + 1] < minimaZ) {
			minimaZ = lista_impactos[j + 1];
		}
		j += (3 + despl);
	}

	// a partir de la información del impacto con la mínima Z, devolver el código del objeto que le
	// corresponde: como la escena no se almacena en ninguna estructura de datos, para devolver el objeto seleccionado
	// utilizar aquí directamente los nombres asignados a los objetos de la escena

	int objeto;
	j = 0;
	for (int i = 0; i < numero_impactos; i++) {
		int despl = lista_impactos[j];
		if (lista_impactos[j + 1] == minimaZ) {
			objeto = lista_impactos[j + 2 + despl];
		}
		j += (3 + despl);
	}
	interfaz.set_objeto_seleccionado(objeto);
	return(objeto);
}

void igvInterfaz::finaliza_seleccion(int TAMANO_LISTA_IMPACTOS, GLuint *lista_impactos) {

	// volver a modo visualizacion OpenGL y obtener el número de impactos  

	int impactos = glRenderMode(GL_RENDER);

	// si hay impactos pasar a procesarlos con la funcion int procesar_impactos(numero_impactos,lista_impactos);
	// obteniendo el objeto seleccionado, si lo hay

	interfaz.escena.obejetoSelecionado(procesar_impactos(impactos, lista_impactos));

	// seleccion terminada, pasar a visualización normal

	interfaz.modo = IGV_VISUALIZAR;

	// establecer la camara en modo visualización

	interfaz.camara.establecerVisualizacion();

}
