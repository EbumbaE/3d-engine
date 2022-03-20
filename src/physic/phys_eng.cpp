#include "phys_eng.h"
#include "colision_sphere.h"

void phys_eng::add(const phys_object &object) {

	objects.push_back(object);

}

void phys_eng::simulate(float delta) {

	for (int i = 0; i < objects.size(); i++) {

		objects[i].iterpoz(delta);

	}

}

void phys_eng::inter_colis() {

	for (int i = 0; i < objects.size(); i++) {
		for (int j = i + 1; j < objects.size(); j++) {

			colision_data col_data = objects[i].get_colider().inter(objects[j].get_colider());
			
			if (col_data.get_does_colision()) {
				
                objects[i].set_speed(glm::reflect(objects[i].get_speed(), glm::normalize(col_data.get_dir())));
                objects[j].set_speed(glm::reflect(objects[j].get_speed(), glm::normalize(-col_data.get_dir())));

			}

		}
	}

}