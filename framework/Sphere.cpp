#include "Sphere.hpp"
#include <cmath>
#include<glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include "vec3_functions.hpp"

Sphere::Sphere(const glm::vec3 &center, float radius) : Shape(), center_(center), radius_(radius) {}

float Sphere::volume() const {
    return 4.0f/3.0f * M_PI * pow(radius_, 3);
}

float Sphere::area() const {
    return 4 * M_PI * pow(radius_, 2);
}

Sphere::Sphere(const std::string &name, const Color &color, const glm::vec3 &center, float radius) : Shape(name, color),
                                                                                                     center_(center),
                                                                                                     radius_(radius) {}

std::ostream& Sphere::print(std::ostream &os) const {
    Shape::print(os);
    os << " Center: " << center_ << " Radius: " << radius_ << std::endl;
    return os;
}

HitPoint Sphere::intersect(Ray &ray) const {
    float distance = 0.0f;
    ray.direction = glm::normalize(ray.direction);
    auto result = glm::intersectRaySphere(ray.origin, ray.direction, center_, radius_ * radius_, distance);
    std::string name = "";
    Color color = {-1, -1, -1};
    if(result){
        name = name_;
        color = color_;
    }
    return HitPoint{result, distance, name, color, distance * ray.direction, ray.direction};
}

std::ostream &operator<<(std::ostream &os, const Sphere &sphere) {

}
