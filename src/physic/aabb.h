#pragma once
#include "colision_data.h"
#include "colider.h"
#include "colision_sphere.h"

class c_aabb : public colider {

public:

	c_aabb(glm::vec3 Center, glm::vec3 Scale) : colider(colider::aabb),
        first_e(Center + glm::vec3(abs(Scale.x / 2.0 - 0.05), abs(Scale.y / 2.0 - 0.05), abs(Scale.z / 2.0 - 0.05))), 
        second_e(Center - glm::vec3(abs(Scale.x / 2.0 - 0.05), abs(Scale.y / 2.0 - 0.05), abs(Scale.z / 2.0 - 0.05))),
        center(Center), scale(Scale) {}

	inline glm::vec3 get_first_e() const {

		return first_e;

	}

	inline glm::vec3 get_scale() const {

		return scale;

	}

	inline glm::vec3 get_second_e() const {

		return second_e;

	}

	inline glm::vec3 get_center() const{

		return center;

	}

	colision_data inter_aabb(const colider &m_model_c);
	colision_data inter_sphere(const colider &model_c);
    colision_data inter_plane(const colider& model_c);

    float DistanceFromPointToAABB(glm::vec3 &point);

	virtual void trans(const glm::vec3 t);

private:

	glm::vec3 first_e, second_e, center, scale;

};