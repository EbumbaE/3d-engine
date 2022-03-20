#include "colider.h"
#include "colision_sphere.h"
#include "aabb.h"
#include "plane.h"


colision_data colider::inter(const colider& model) const{

	//cout << type << " " << model.get_type() << " " << sphere << "\n";

	if (type == sphere && model.get_type() == sphere) {

		colision_sphere* sphere = (colision_sphere*)this;
		return sphere->inter_sphere(model);
	
	}

	if (type == aabb && model.get_type() == aabb) {

		c_aabb* aabb = (c_aabb*)this;
		return aabb->inter_aabb(model);

	}
	
	if (type == aabb && model.get_type() == sphere) {

		c_aabb* aabb = (c_aabb*)this;
		return aabb->inter_sphere(model);

	}
	
	if (type == sphere && model.get_type() == aabb) {

		colision_sphere* sphere = (colision_sphere*)this;
		return sphere ->inter_aabb(model);

	}
	
    if (type == plane && model.get_type() == sphere) {

        c_plane* plane = (c_plane*)this;
        return plane->inter_sphere((colision_sphere&)model);

    }

    if (type == sphere && model.get_type() == plane) {

        colision_sphere* sphere = (colision_sphere*)this;
        return sphere->inter_plane(model);

    }

    if (type == aabb && model.get_type() == plane) {

        c_aabb* aabb = (c_aabb*)this;
        return aabb->inter_plane(model);

    }

    if (type == plane && model.get_type() == aabb) {

        c_plane* plane = (c_plane*)this;
        return plane->inter_aabb(model);

    }

	cout << "colider error \n";

	return colision_data(false, glm::vec3(0.0f, 0.0f, 0.0f));

}