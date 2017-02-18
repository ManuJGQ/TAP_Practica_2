#include "PagLight.h"
#include <iostream>

PagLight::PagLight(){}

PagLight::PagLight(glm::vec3 _positionDirection, float _Ia, float _Id, float _Is,
	char _light, float _shininess){

	if (_light == 'P') {

		light = 'P';

		position = _positionDirection;

		Ia = _Ia;
		Id = _Id;
		Is = _Is;

		shininess = _shininess;

	}
	else if (_light == 'D') {

		light = 'D';

		direction = _positionDirection;

		Ia = _Ia;
		Id = _Id;
		Is = _Is;

		shininess = _shininess;

	}
}


PagLight::PagLight(glm::vec3 _position, glm::vec3 _direction, float _Ia, float _Id, float _Is,
	float _y, float _s, float _shininess){

	light = 'S';

	position = _position;
	direction = _direction;

	Ia = _Ia;
	Id = _Id;
	Is = _Is;

	y = _y;
	s = _s;

	shininess = _shininess;

}

PagLight::PagLight(const PagLight & orig) {
	light = orig.light;
	if (light == 'S') {
		position = orig.position;
		direction = orig.direction;

		Ia = orig.Ia;
		Id = orig.Id;
		Is = orig.Is;


		y = orig.y;
		s = orig.s;

		shininess = orig.shininess;
	}
	else {
		if (light == 'P') {
			position = orig.position;

			Ia = orig.Ia;
			Id = orig.Id;
			Is = orig.Is;

			shininess = orig.shininess;
		}
		else {
			direction = orig.direction;

			Ia = orig.Ia;
			Id = orig.Id;
			Is = orig.Is;

			shininess = orig.shininess;
		}
	}
}

void PagLight::operator=(const PagLight & orig){
	*this = orig;
}

PagLight::~PagLight(){}
