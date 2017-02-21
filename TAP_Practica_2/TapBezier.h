#pragma once

#include "Pag3DObject.h"

#include <vector>
#include "Structs.h"

class TapBezier: public Pag3DObject {
	glm::mat4 ModelMatrix;

	Structs::PuntosVertices pa;
	Structs::PuntosVertices pb;
	Structs::PuntosVertices pc;
	Structs::PuntosVertices pd;

	std::vector<Structs::PuntosVertices> curva;

public:

	TapBezier();
	TapBezier(Structs::PuntosVertices _pa, Structs::PuntosVertices _pb, Structs::PuntosVertices _pc,
		Structs::PuntosVertices _pd);
	void createObject() override;
	void draw(glm::mat4 ViewMatrix, glm::mat4 ProjectionMatrix, PagRenderer* renderer, std::pair<std::string, PagShaderProgram*> shader, PagLight* light, int ns) override;
	~TapBezier();
};

