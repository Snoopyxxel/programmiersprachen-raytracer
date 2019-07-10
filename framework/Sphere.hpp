#ifndef RAYTRACER_SPHERE_HPP
#define RAYTRACER_SPHERE_HPP

#include "Shape.hpp"
#include "hitpoint.hpp"
#include "ray.hpp"
#include <glm/vec3.hpp>
#include <ostream>

class Sphere : public Shape {
public:

    Sphere(const glm::vec3 &center, float radius);

    Sphere(const std::string &name, const Material &material, const glm::vec3 &center, float radius);

    float area() const override;

    float volume() const override;

    std::ostream& print(std::ostream &os = std::cout) const override;

    friend std::ostream &operator<<(std::ostream &os, const Sphere &sphere);

    HitPoint intersect(Ray &ray) const override;

private:
    glm::vec3 center_;
    float radius_;
};


#endif //RAYTRACER_SPHERE_HPP
