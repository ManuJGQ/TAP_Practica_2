#ifndef __IGVINTERFAZ
#define __IGVINTERFAZ

#include <glut.h>
#include <string>

#include "igvEscena3D.h"
#include "igvCamara.h"

using namespace std;

typedef enum {
	IGV_VISUALIZAR,
	IGV_SELECCIONAR
} modoInterfaz;

class igvInterfaz {
	protected:
		// Atributos
		int ancho_ventana; // ancho inicial de la ventana de visualizacion
		int alto_ventana;  // alto inicial de la ventana de visualizacion

		igvPunto3D vistas[4]; 
		igvPunto3D va;

		bool formato;
		bool vista;
		bool perspectiva;


		igvEscena3D escena; // escena que se visualiza en la ventana definida por igvInterfaz
		igvCamara camara; // cámara que se utiliza para visualizar la escena

///// Apartado D: atributos para la selección mediante el ratón
		modoInterfaz modo; // IGV_VISUALIZAR: en la ventana se va a visualizar de manera normal la escena, 
		                   // IGV_SELECCIONAR: se ha pulsado sobre la ventana de visualización, la escena se debe
		                   // visualizar en modo selección para el cálculo de la lista de impactos
		int cursorX,cursorY; // pixel de la pantalla sobre el que está situado el ratón, por pulsar o arrastrar

		int objeto_seleccionado; // código del objeto seleccionado, -1 si no hay ninguno
		
		bool boton_retenido; // indica si el botón está pulsado (true) o se ha soltado (false)

	public:
		// Constructores por defecto y destructor
		igvInterfaz();
		~igvInterfaz();

		int i;
		int ang;
		double planos[2];

		bool animacion;

		int pierna;
		int brazo;
		int cabezaS;
		int cabezaN;

		bool bpierna;
		bool bbrazo;
		bool bcabezaS;
		bool bcabezaN;


		// Metodos estáticos
		// callbacks de eventos
		static void set_glutKeyboardFunc(unsigned char key, int x, int y); // metodo para control de eventos del teclado
		static void set_glutReshapeFunc(int w, int h); // método que define la camara de vision y el viewport
		                                               // se llama automáticamente cuano se camba el tamaño de la ventana
		static void set_glutDisplayFunc(); // método para visualizar la escena
    static void set_glutIdleFunc(); // método para animar la escena

///// Apartado D: métodos para el control de la pulsación y el arrastre del ratón
		static void  set_glutMouseFunc(GLint boton,GLint estado,GLint x,GLint y); // control de pulsacion del raton
    static void  set_glutMotionFunc(GLint x,GLint y); // control del desplazamiento del raton con boton pulsado


		// Metodos

///// Apartado D: métodos a implementar para realizar la seleccion mediante lista de impactos
		void inicia_seleccion(int TAMANO_LISTA_IMPACTOS, GLuint *lista_impactos);
		void finaliza_seleccion(int TAMANO_LISTA_IMPACTOS, GLuint *lista_impactos);

		// crea el mundo que se visualiza en la ventana
		void crear_mundo(void);

		// inicializa todos los parámetros para crear una ventana de visualización
		void configura_entorno(int argc, char** argv, // parametros del main
			                     int _ancho_ventana, int _alto_ventana, // ancho y alto de la ventana de visualización
			                     int _pos_X, int _pos_Y, // posicion inicial de la ventana de visualización
													 string _titulo // título de la ventan de visualización
													 ); 
		void inicializa_callbacks(); // inicializa todas los callbacks

		void inicia_bucle_visualizacion(); // visualiza la escena y espera a eventos sobre la interfaz

		// métodos get_ y set_ de acceso a los atributos
		int get_ancho_ventana(){return ancho_ventana;};
		int get_alto_ventana(){return alto_ventana;};

		void set_ancho_ventana(int _ancho_ventana){ancho_ventana = _ancho_ventana;};
		void set_alto_ventana(int _alto_ventana){alto_ventana = _alto_ventana;};

		igvPunto3D get_vistas(int i){return vistas[i];};
		igvPunto3D get_va(){return va;};
		void set_va( const double& x, const double& y, const double& z){va.set(x,y,z);};

		bool get_formato(){return formato;};
		void set_formato(bool _formato){formato=_formato;};
		bool get_vista(){return vista;};
		void set_vista(bool _vista){vista=_vista;};
		bool get_perspectiva(){return perspectiva;};
		void set_perspectiva(bool _perspectiva){perspectiva=_perspectiva;};

		int get_objeto_seleccionado(){return objeto_seleccionado;};
		void set_objeto_seleccionado(int _objetoseleccionado){objeto_seleccionado=_objetoseleccionado;};


};



#endif
