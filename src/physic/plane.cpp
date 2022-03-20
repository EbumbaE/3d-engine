#include "plane.h"

void c_plane::trans(const glm::vec3 t) {

    normal += t;

}

c_plane c_plane::normalize() const{

	float nl = glm::length(normal);

	return c_plane(normal / nl, distance / nl);

}

colision_data c_plane::inter_sphere(const colider& model_c){

    colision_sphere model = (colision_sphere&)model_c;

	float dfsc = fabs(-glm::dot(normal, model.get_center()) + distance);  // dist from sphere center
	float dfs = dfsc - model.get_radius(); // dist from sphere
	
	return colision_data(dfs < 0, normal * dfs);

}

colision_data c_plane::inter_aabb(const colider& model_c) {

    c_aabb model = (c_aabb&)model_c;

    glm::vec3 center = model.get_center();
    glm::vec3 ext = model.get_first_e() - center;

    float radius = ext.x * fabs(normal.x) + ext.y * fabs(normal.y) + ext.z * fabs(normal.z);
    float dist = fabs(glm::dot(normal, center) - distance);

    return colision_data(dist <= radius, normal * dist);

}