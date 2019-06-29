#include "Box.hpp"
#include <stdexcept>

Box::Box(const glm::vec3 &min, const glm::vec3 &max) : min_(min), max_(max) {
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
