#include <glm/vec3.hpp>
#include "Shape.hpp"
#include <memory>

Shape::Shape() : name_("shape-default"),
                 material_(std::make_shared<Material>("default_material", Color{1,1,1}, Color{1,1,1}, Color{1,1,1}, 1)){
                 world_transformation_= glm::mat4x4{glm::vec4{1.0f,0.0f,0.0f,0.0f},  // default - Einheitsmatrix
                                                    glm::vec4{0.0f,1.0f,0.0f,0.0f},
                                                    glm::vec4{0.0f,0.0f,1.0f,0.0f},
                                                    glm::vec4{0.0f,0.0f,0.0f,1.0f}};
                 world_transformation_inv_ = glm::inverse(world_transformation_);}

Shape::Shape(const std::string &name, const std::shared_ptr<Material> &material) : name_(name), material_(material){
                 world_transformation_= glm::mat4x4{glm::vec4{1.0f,0.0f,0.0f,0.0f},  // default - Einheitsmatrix
                                                    glm::vec4{0.0f,1.0f,0.0f,0.0f},
                                                    glm::vec4{0.0f,0.0f,1.0f,0.0f},
                                                    glm::vec4{0.0f,0.0f,0.0f,1.0f}};
                 world_transformation_inv_ = glm::inverse(world_transformation_);} 
                 

std::ostream& operator<<(std::ostream &os, const Shape &shape) {
    return shape.print(os);
}

std::ostream& Shape::print(std::ostream &os) const {
    os << "Name: " << name_ << " | Material: " << *material_;
    return os;
}

std::string Shape::get_name(){
        return name_;
    };
