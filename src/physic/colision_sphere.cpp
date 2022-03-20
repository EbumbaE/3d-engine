#include "colision_sphere.h"

void colision_sphere::trans(const glm::vec3 t) {

	center += t;

}

colision_data colision_sphere::inter_sphere(const colider& model_c){

    colision_sphere model = (colision_sphere&)model_c;

	double rd = radius + model.radius;                 
	glm::vec3 cdv = model.get_center() - center;
	double cd = glm::length(cdv);
	
	cdv /= cd;

	return colision_data(cd < rd, cdv);
        
}

colision_data colision_sphere::inter_aabb(const colider& model_c) {

    c_aabb model = (c_aabb&)model_c;
    
    glm::vec3 aabb_center = model.get_center();

    float distance = model.DistanceFromPointToAABB(center);
    glm::vec3 distance_center = aabb_center - center;

    return colision_data(distance < radius, distance_center / sqrtf(distance));
	
}

colision_data colision_sphere::inter_plane(const colider &model_c) {

    c_plane model = (c_plane&)model_c;

    float dfsc = fabs(glm::dot(model.get_normal(), center) + model.get_distance());  // dist from sphere center
    float dfs = dfsc - radius; // dist from sphere

    return colision_data(dfs < 0, model.get_normal() * dfs);

}