#include "Sphere.hpp"
#include <cmath>

Sphere::Sphere(const glm::vec3 &center, float radius) : center_(center), radius_(radius) {}

float Sphere::volume() const {
    return 4.0f/3.0f * M_PI * pow(radius_, 3);
}

float Sphere::area() const {
    return 4 * M_PI * pow(radius_, 2);
}
