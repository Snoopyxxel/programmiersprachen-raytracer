#include <glm/vec3.hpp>
#include "Shape.hpp"

Shape::Shape() : name_(""), material_(std::make_shared<Material>("default_material", Color{1,1,1}, Color{1,1,1}, Color{1,1,1}, 1)) {}
Shape::Shape(const std::string &name, const std::shared_ptr<Material> &material) : name_(name), material_(material) {}

std::ostream& operator<<(std::ostream &os, const Shape &shape) {
    return shape.print(os);
}

std::ostream& Shape::print(std::ostream &os) const {
    os << "Name: " << name_ << " | Material: " << material_;
    return os;
}