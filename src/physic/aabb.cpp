#include "aabb.h"

void c_aabb::trans(const glm::vec3 t) {

	first_e += t;
	second_e += t;

}

colision_data c_aabb::inter_aabb(const colider &model_c) {

    c_aabb model = (c_aabb&)model_c;
    
    glm::vec3 d1 = model.get_first_e() - second_e;
    glm::vec3 d2 = first_e - model.get_second_e();

	glm::vec3 dist = glm::max(d1, d2);
    
    dist /= glm::length(dist);
    

    bool f = model.get_second_e().x <= first_e.x && model.get_first_e().x >= second_e.x &&
             model.get_second_e().y <= first_e.y && model.get_first_e().y >= second_e.y &&
             model.get_second_e().z <= first_e.z && model.get_first_e().z >= second_e.z;
    
	return colision_data(f, dist);
}

float c_aabb::DistanceFromPointToAABB(glm::vec3& point) {

    auto max = [&](float a, float b) -> float {
        if (a > b)
            return a;
        return b;
    };
    auto min = [&](float a, float b) -> float {
        if (a < b)
            return a;
        return b;
    };
    auto sqr = [&](float a) -> float {
        return a * a;
    };

    float x = max(second_e.x, min(point.x, first_e.x));
    float y = max(second_e.y, min(point.y, first_e.y));
    float z = max(second_e.z, min(point.z, first_e.z));

    return sqr(x - point.x) + sqr(y - point.y) + sqr(y - point.y);

}

colision_data c_aabb::inter_sphere(const colider& model_c){

    colision_sphere model = (colision_sphere&)model_c;
    glm::vec3 sphere_center = model.get_center();
    
    float distance = DistanceFromPointToAABB(sphere_center);

    float radius = model.get_radius();
    glm::vec3 distance_center = sphere_center - center;              //change
    
	return colision_data(distance < radius * radius, distance_center / sqrtf(distance));

}

colision_data c_aabb::inter_plane(const colider& model_c) {

    c_plane model = (c_plane&)model_c;
    
    glm::vec3 normal = model.get_normal();
    float distance = model.get_distance();
    glm::vec3 ext = first_e - center;

    float radius = ext.x * fabs(normal.x) + ext.y * fabs(normal.y) + ext.z * fabs(normal.z);
    float dist = fabs(glm::dot(normal, center) - distance);

    return colision_data(dist <= radius, normal * dist);
    
}