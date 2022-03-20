#pragma once
#include "../include.h"

class colision_data {

public:

	colision_data(const bool d_col, const glm::vec3 diraction) :
		colision(d_col), direction(diraction) {}

	inline bool get_does_colision() const {
	
		return colision;
	
	}
	
	inline float get_dist() const {
		
        return glm::length(direction);

	}

	inline const glm::vec3 get_dir() const {

		return direction;

	}

private:

	const bool colision;
	const glm::vec3 direction;

};