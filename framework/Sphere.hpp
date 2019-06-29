#include "Shape.hpp"
#include <glm/vec3.hpp>

#ifndef RAYTRACER_SPHERE_HPP
#define RAYTRACER_SPHERE_HPP


class Sphere : public Shape {
public:
    Sphere(const glm::vec3 &center, float radius);

    float area() const override;

    float volume() const override;

private:
    glm::vec3 center_;
    float radius_;
};


#endif //RAYTRACER_SPHERE_HPP
