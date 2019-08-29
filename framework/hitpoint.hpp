#ifndef RAYTRACER_HITPOINT_HPP
#define RAYTRACER_HITPOINT_HPP

#include <string>
#include <glm/vec3.hpp>
#include <memory>
#include "Material.hpp"

struct HitPoint {
    bool intersected;
    float distance;
    std::string name;
    std::shared_ptr<Material> material;
    glm::vec3 point_;
    glm::vec3 ray_direction_;
};

#endif
