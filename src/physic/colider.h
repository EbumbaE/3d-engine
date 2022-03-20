#pragma once
#include "colision_data.h"
#include "../include.h"
#include "counter.h"

class colider : public counter{

public:

	enum {

		sphere, 
		aabb,
        plane

	};

	colider(int t):
		counter(), type(t) {}

	colision_data inter(const colider& model) const;

	virtual glm::vec3 get_center() const{
	
		return glm::vec3(0.0f, 0.0f, 0.0f);

	}

	virtual void trans(const glm::vec3 t) {};

	inline int get_type() const {

		return type;

	}

private:

	int type;

};