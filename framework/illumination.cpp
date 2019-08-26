#include <glm-0.9.5.3/glm/glm.hpp>
#include "illumination.hpp"
#include "scene.hpp"

bool check_obstruction(glm::vec3 const &p1, glm::vec3 const &p2) {
    return false;
}


Color phong(Ray const &ray, HitPoint const &intersection, std::shared_ptr<Shape> const &inters_o, Scene const& scene) {
    Color ambient = scene.ambient_light_ * intersection.material->ka;


    return ambient;
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
