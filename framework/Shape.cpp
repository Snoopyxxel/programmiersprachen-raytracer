#include <glm/vec3.hpp>
#include "Shape.hpp"

Shape::Shape(const std::string &name, const Color &color) : name_(name), color_(color) {}

std::ostream& operator<<(std::ostream &os, const Shape &shape) {
    return shape.print(os);
}

std::ostream& Shape::print(std::ostream &os) const {
    os << "Name: " << name_ << " | Color: " << color_;
    return os;
}