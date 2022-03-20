#pragma once
#include "colider.h"
#include "colision_data.h"
#include "colision_sphere.h"

class c_plane : public colider{

public:

	c_plane(const glm::vec3 normal, const float dist) : colider(colider::plane),
		normal(normal), distance(dist) {}

    virtual void trans(const glm::vec3 t);

	inline const glm::vec3 get_normal() const {

		return normal;

	}

	inline const float get_distance() const {

		return distance;

	}

    c_plane normalize() const;

    colision_data inter_sphere(const colider& model);
    colision_data inter_aabb(const colider& model);

private:

    glm::vec3 normal;
	float distance;

};