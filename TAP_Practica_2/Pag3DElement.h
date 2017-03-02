#pragma once

#include <glew.h>
#include <glfw3.h>
#include "gtc\matrix_transform.hpp"
#include "PagLight.h"
#include "PagShaderProgram.h"

class PagRenderer;

class Pag3DElement{
	glm::mat4 ModelMatrix;
public:
	virtual void draw(glm::mat4 ViewMatrix, glm::mat4 ProjectionMatrix, PagRenderer* renderer, std::pair<std::string,PagShaderProgram*> shader, PagLight* light, int ns) = 0;
	virtual void createObject() = 0;
	Pag3DElement();
	virtual ~Pag3DElement();
};

