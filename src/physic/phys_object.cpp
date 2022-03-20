#include "phys_object.h"

phys_object::phys_object(const phys_object& model) : 
    pozition(model.pozition), speed(model.speed), old_pozition(model.old_pozition), c(model.c) 
{ 
    c->add_c(); 
}

phys_object::~phys_object() {

	if (c->remove_c()) {

		delete c;

	}
}

void phys_object::iterpoz(float delta) {

	pozition += speed * delta;

}	