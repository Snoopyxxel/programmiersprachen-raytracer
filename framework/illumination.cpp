#include <glm-0.9.5.3/glm/glm.hpp>
#include "illumination.hpp"
#include "scene.hpp"

bool obstructed(glm::vec3 const& p1, glm::vec3 const& p2, Scene const& scene) {
    Ray ray{p1, glm::normalize(p2 - p1)};

    for (auto const& obj : scene.shape_list){
        HitPoint intersection = obj->intersect(ray);
        if (intersection.distance - 0.0005f > 0.0f && intersection.distance + 0.0005f < glm::distance(p1, p2)){
            return true;
        }
    }
    return false;
}


Color phong(Ray const &ray, HitPoint const &intersection, std::shared_ptr<Shape> const& inters_o, Scene const& scene) {

    Color result = scene.ambient_light_ * intersection.material->ka;

    for (auto const& light : scene.light_list_){
        if(!obstructed(intersection.intersection_point, light->pos_, scene)){
            auto to_light = glm::normalize(light->pos_ - intersection.intersection_point);
            auto normal = inters_o->normal(intersection.intersection_point);
            auto angle = glm::dot(to_light, normal);
            if (angle > 0.0f) {
                Color diffuse = light->luminosity_ * angle * intersection.material->kd;
                result += diffuse;
            }

            glm::vec3 from_light = glm::normalize(intersection.intersection_point - light->pos_);
            glm::vec3 r = glm::normalize(from_light - (2 * glm::dot(from_light, normal) * normal));
            Color specular = powf(glm::dot(r, glm::normalize(-intersection.intersection_ray_direction)), intersection.material->m) * light->luminosity_ * intersection.material->ks;
            if (specular > 0.0f){
                result += specular;
            }
        }
    }


    return result;
}

/*float phong(glm::vec3 const &in) {
    std::vector<std::pair<std::shared_ptr<Light>,float>> eval_lights;
    for (auto const& light : light_list_){
        if (!obstructed(in, light->pos_)){
            eval_lights.push_back({light, glm::distance(in, light->pos_)});,

        }
    }
}*/

/*
for all light sources in scene:

    check if any object is between light source and object, if yes, do nothing

    if no object between light source and intersection, add light source to those evaluated in Equation

    store distance of light sources to intersection and with the distances compute brightness factor

    use brightness factor and the material coefficients to calculate illumination with phong equation
*/
