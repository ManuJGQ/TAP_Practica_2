#pragma once

#include <glew.h>
#include <glfw3.h>
#include "gtc\matrix_transform.hpp"

class PagMaterial{
	glm::vec3 Ka;
	glm::vec3 Kd;
	glm::vec3 Ks;
public:
	PagMaterial();
	PagMaterial(glm::vec3 _Ka, glm::vec3 _Kd, glm::vec3 _Ks);
	PagMaterial(const PagMaterial &orig);
	glm::vec3 getKa() { return Ka; }
	glm::vec3 getKd() { return Kd; }
	glm::vec3 getKs() { return Ks; }
	~PagMaterial();
};

