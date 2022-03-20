#pragma once
#include "colision_data.h"
#include "colider.h"
#include "aabb.h"
#include "plane.h"

class colision_sphere : public colider {

public:

	colision_sphere(glm::vec3 cent, float rad) : colider(colider::sphere),
		center(cent), radius(abs(rad - 0.05)) {}

	inline glm::vec3 get_center() const {
	
		return center;
	
	}

	inline float get_radius() const {
		
		return radius;

	}

	colision_data inter_sphere(const colider &model);
	colision_data inter_aabb(const colider &model_c);
    colision_data inter_plane(const colider &model_c);

	virtual void trans(const glm::vec3 t);

private:

	glm::vec3 center;
	float radius;

};