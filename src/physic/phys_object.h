#pragma once
#include "colider.h"

class phys_object {

public:

	phys_object(colider *colider, const glm::vec3 velocity) :
		pozition(colider->get_center()), speed(velocity), old_pozition(colider->get_center()), c(colider) {}

	phys_object(const phys_object &model);

	phys_object operator=(phys_object model);
	
	virtual ~phys_object();

    void iterpoz(float delta);

	inline const glm::vec3 get_pozition() const {

		return pozition;

	}

	inline const glm::vec3 get_speed() const {

		return speed;

	}

	inline const colider& get_colider() {

		glm::vec3 t = pozition - old_pozition;
		old_pozition = pozition;

		c->trans(t);

		return *c;

	}

	inline void set_speed(const glm::vec3 setspeed) {

		speed = setspeed;

	}

private:

	glm::vec3 pozition, speed, old_pozition;
	
	colider *c;														

};