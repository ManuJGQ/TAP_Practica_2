#pragma once

#include <glew.h>
#include <glfw3.h>
#include "gtc\matrix_transform.hpp"
#include <string>


class PagLight{
public:

	char light; // P - Puntuales  D - Direccional  S - Spot

	glm::vec3 position;

	glm::vec3 direction;

	float Ia;
	float Id;
	float Is;

	float shininess;

	float y;
	float s;

	PagLight();
	PagLight(glm::vec3 _positionDirection, float _Ia, float _Id, float _Is, char _light, float _shininess);
	PagLight(glm::vec3 _position, glm::vec3 _direction, float _Ia, float _Id, float _Is, float _y, float _s, float _shininess);
	PagLight(const PagLight &orig);
	void operator = (const PagLight &orig);
	~PagLight();
};

