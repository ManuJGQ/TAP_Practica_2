#include "PagRenderer.h"

#include <iostream>
#include <string>

#include <set>

#include <algorithm>
#include "dirent.h"

#include <glew.h>
#include <glfw3.h>
#include "gtc\matrix_transform.hpp"
#include <filesystem>

bool has_suffix(const std::string &str, const std::string &suffix) {
	return str.size() >= suffix.size() &&
		str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

PagRenderer::PagRenderer(){
	// Leemos los datos y txt del usuario
	int perfiles = 8;

	ficheros = new Structs::Fichero[perfiles];

	int j = perfiles;
	while (j != 0) {
		std::string archivo;
		if (j == 1)archivo = "b1-in.txt";
		if (j == 2)archivo = "b2-in.txt";
		if (j == 3)archivo = "b3-in.txt";
		if (j == 4)archivo = "b4-in.txt";
		if (j == 5)archivo = "b5-in.txt";
		if (j == 6)archivo = "b6-in.txt";
		if (j == 7)archivo = "b7-in.txt";
		if (j == 8)archivo = "b8-in.txt";

		std::string _nTextura;

		if (j == 1)_nTextura = "bb8";
		if (j == 2)_nTextura = "bb8-c2";
		if (j == 3)_nTextura = "bb8-ca";
		if (j == 4)_nTextura = "bb8-ca-top";
		if (j == 5)_nTextura = "bb8-eye";
		if (j == 6)_nTextura = "bb8-eye";
		if (j == 7)_nTextura = "bb8-eye";
		if (j == 8)_nTextura = "bb8-eye";


		std::string _nBump;

		if (j == 1)_nBump = "bump1";
		if (j == 2)_nBump = "bump3";
		if (j == 3)_nBump = "bump2";
		if (j == 4)_nBump = "bump3";
		if (j == 5)_nBump = "bump3";
		if (j == 6)_nBump = "bump3";
		if (j == 7)_nBump = "bump3";
		if (j == 8)_nBump = "bump3";


		Structs::Fichero _fichero;
		_fichero.nombreAlumno = archivo;
		_fichero.archivoIN = archivo;
		_fichero.nTextura = _nTextura;
		_fichero.nBump = _nBump;
		_fichero.nSemiTrasnparente = "Limpio";
		ficheros[perfiles - j] = _fichero;
		j--;
	}

	int slices = 100;

	for (int i = 0; i < perfiles; i++) { ficheros[i].numSlices = slices; }

	//Creamos la jerarquia de objetos
	objects = Pag3DGroup(ficheros, perfiles);

}

void PagRenderer::cargarEscena() {
	//Cargamos las luces
	lights.push_back(PagLight(glm::vec3(30.0, 90.0, -90.0), glm::vec3(-0.23, -0.69, 0.69), 0.2f, 0.5f, 0.3f, 20.0f, 5.0f, 50.0f));
	lights.push_back(PagLight(glm::vec3(60.0, 90.0, 0.0), 0.1f, 0.125f, 0.075f, 'P', 50.0f));
	lights.push_back(PagLight(glm::vec3(-60.0, 90.0, 0.0), 0.1f, 0.125f, 0.075f, 'P', 50.0f));

	//Creamos las Geometrias y Topologias de los diferentes objetos que componen la escena
	objects.createObject();


	glm::mat4 ModelMatrix(1.0);

	ModelMatrix *= glm::translate(glm::mat4(), glm::vec3(-8.0f, 45.7f, -8.9f));

	ModelMatrix *= glm::rotate(glm::mat4(1.0f), 0.70f, glm::vec3(0.0f, 1.0f, 0.0f));

	ModelMatrix *= glm::rotate(glm::mat4(), -1.22f, glm::vec3(1.0f, 0.0f, 0.0f));

	ModelMatrix *= glm::translate(glm::mat4(), glm::vec3(0.0f, -2.0f, 0.0f));

	objects.setModelMatrix(ModelMatrix, 5);

	glm::mat4 ModelMatrix2(1.0);

	ModelMatrix2 *= glm::translate(glm::mat4(), glm::vec3(-1.1f, 48.0f, -10.0f));

	ModelMatrix2 *= glm::rotate(glm::mat4(1.0f), 0.08f, glm::vec3(0.0f, 1.0f, 0.0f));

	ModelMatrix2 *= glm::rotate(glm::mat4(), -1.05f, glm::vec3(1.0f, 0.0f, 0.0f));

	ModelMatrix2 *= glm::translate(glm::mat4(), glm::vec3(0.0f, -2.0f, 0.0f));

	objects.setModelMatrix(ModelMatrix2, 6);

	glm::mat4 ModelMatrix3(1.0);

	ModelMatrix3 *= glm::translate(glm::mat4(), glm::vec3(-2.0f, -0.5f, 2.0f));

	objects.setModelMatrix(ModelMatrix3, 8);

	//Cargamos todas las Texturas del directorio Textures

	DIR *dir = opendir("Textures/");

	dirent *entry;
	while ((entry = readdir(dir)) != nullptr) {
		if (has_suffix(entry->d_name, ".png")) {

			std::string name = std::string(entry->d_name);
			int ind = name.find_last_of(".");
			std::string nombreSinExt = name.substr(0, ind);
			std::string path = "Textures/" + name;

			textures.insert_or_assign(nombreSinExt, PagTexture(path, GLuint(textures.size())));
		}
	}
	closedir(dir);

	//Cargamos todos los shaders
	std::vector<std::string> nombreShaders;

	DIR *dirS = opendir("Textures/..");

	dirent *entryS;

	std::set<std::string> shadersNames;

	while ((entryS = readdir(dirS)) != nullptr) {
		if (has_suffix(entryS->d_name, ".frag")) {

			entryS = readdir(dirS);

			if (has_suffix(entryS->d_name, ".vert")) {

				std::string name = std::string(entryS->d_name);
				int ind = name.find_last_of(".");
				name = name.substr(0, ind);

				ind = name.find_last_of("-");
				std::string name2 = name.substr(0, ind);


				if (shadersNames.find(name2) == shadersNames.end()) {
					nombreShaders.push_back(name2);
					shadersNames.insert(name2);
				}

			}

		}
	}
	closedir(dirS);

	nombreShader = nombreShaders[0];

		for (int i = 0; i < lights.size(); i++) {
			std::string name = nombreShader + "-";
			char l = lights[i].light;
			name += l;
			PagShaderProgram* shader = new PagShaderProgram();
			shader->createShaderProgram(name.c_str());
			shadersUtilizados.push_back(std::pair<std::string, PagShaderProgram*>(name, shader));
		}
}

void PagRenderer::pintarEscena(glm::mat4 ViewMatrix, glm::mat4 ProjectionMatrix) {

		glEnable(GLenum(GL_BLEND));
		glDepthFunc(GLenum(GL_LEQUAL));

		for (int i = 0; i < lights.size(); i++) {

			if (i == 0) { glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); }
			else { glBlendFunc(GL_SRC_ALPHA, GL_ONE); }

			objects.draw(ViewMatrix, ProjectionMatrix, this, shadersUtilizados[i], &lights[i], i);
			objects2.draw(ViewMatrix, ProjectionMatrix, this, shadersUtilizados[i], &lights[i], i);
		}
}

PagRenderer::~PagRenderer() {
	delete[] ficheros;
}
