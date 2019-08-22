#ifndef RAYTRACER_LIGHT_HPP
#define RAYTRACER_LIGHT_HPP


#include <glm/vec3.hpp>

struct Light {
    glm::vec3 pos_;
    float intensity_;
};


#endif //RAYTRACER_LIGHT_HPP
