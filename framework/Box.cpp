#include "Box.hpp"
#include "vec3_functions.hpp"
#include <stdexcept>
#include <glm-0.9.5.3/glm/gtx/intersect.hpp>
#include <vector>
#include <set>

Box::Box(const glm::vec3 &min, const glm::vec3 &max) : Shape(), min_(min), max_(max) {
    if(min.x >= max.x or min.y >= max.y or min.z >= max.z){
        throw std::invalid_argument("min should be smaller than max in every coordinate!");
    }
}

float Box::area() const {
    float breite = abs(min_.z - max_.z);
    float tiefe = abs(min_.x - max_.x);
    float hoehe = abs(min_.y - max_.y);
    return 2 * (breite * tiefe + breite * hoehe + tiefe * hoehe);
}

float Box::volume() const {
    float breite = abs(min_.z - max_.z);
    float tiefe = abs(min_.x - max_.x);
    float hoehe = abs(min_.y - max_.y);
    return breite * hoehe * tiefe;
}

Box::Box(const std::string &name, const Color &color, const glm::vec3 &min, const glm::vec3 &max) : Shape(name, color), min_(min), max_(max) {}

std::ostream& Box::print(std::ostream &os) const {
    Shape::print(os);
    os << " Minimum: " << min_ << " Maximum: " << max_ << std::endl;
    return os;
}

HitPoint Box::intersect(Ray &ray) const {
    Ray ray1 = {ray.origin, -(ray.direction)};

    ray1.direction = glm::normalize(ray1.direction);

    float distance[6];
    bool face_intersect[6];
    std::set<float> checked_distance;


    face_intersect[0] = glm::intersectRayPlane(ray1.origin, ray1.direction, min_, glm::vec3{0, 0, 1}, distance[0]); // x, y plane
    face_intersect[1] = glm::intersectRayPlane(ray1.origin, ray1.direction, min_, glm::vec3{0, 1, 0}, distance[1]); // x, z plane
    face_intersect[2] = glm::intersectRayPlane(ray1.origin, ray1.direction, min_, glm::vec3{1, 0, 0}, distance[2]); // y, z plane
    face_intersect[3] = glm::intersectRayPlane(ray1.origin, ray1.direction, max_, glm::vec3{0, 0, 1}, distance[3]);
    face_intersect[4] = glm::intersectRayPlane(ray1.origin, ray1.direction, max_, glm::vec3{0, 1, 0}, distance[4]);
    face_intersect[5] = glm::intersectRayPlane(ray1.origin, ray1.direction, max_, glm::vec3{1, 0, 0}, distance[5]);

    for(int i = 0; i < 6; ++i){
        if(face_intersect[i]){
            glm::vec3 intersection = ray.origin + -distance[i] * ray.direction;
            if(intersection.x >= min_.x and intersection.x <= max_.x and intersection.y >= min_.y and intersection.y <= max_.y and intersection.z >= min_.z and intersection.z <= max_.z){
                checked_distance.insert(-distance[i]);
            }
        }
    }

    std::string name = "";
    Color color = {-1, -1, -1};
    bool result = false;
    if(*checked_distance.begin() != 0){
        name = name_;
        color = color_;
        result = true;
    }

    return HitPoint{result, *checked_distance.begin(), name, color, ray.origin + *checked_distance.begin() * ray.direction, ray.direction};
}