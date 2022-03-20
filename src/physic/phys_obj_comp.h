#pragma once
#include "phys_eng.h"

class phys_obj_comp {

public:

	phys_obj_comp(const phys_object *object) :
		ph_object(object) {}

	virtual void update(float delta, glm::vec3 objpoz);

private:

	const phys_object *ph_object;

};