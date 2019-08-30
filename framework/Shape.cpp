#include <glm/vec3.hpp>
#include "Shape.hpp"
#include <memory>

Shape::Shape() : name_("shape-default"),
                 material_(std::make_shared<Material>("default_material", Color{1,1,1}, Color{1,1,1}, Color{1,1,1}, 1)){
                 world_transformation_= glm::mat4{glm::vec4{1.0f,0.0f,0.0f,0.0f},  // default - Einheitsmatrix
                                                    glm::vec4{0.0f,1.0f,0.0f,0.0f},
                                                    glm::vec4{0.0f,0.0f,1.0f,0.0f},
                                                    glm::vec4{0.0f,0.0f,0.0f,1.0f}};
                 world_transformation_inv_ = glm::inverse(world_transformation_);}

Shape::Shape(const std::string &name, const std::shared_ptr<Material> &material) : name_(name), material_(material){
                 world_transformation_= glm::mat4{glm::vec4{1.0f,0.0f,0.0f,0.0f},  // default - Einheitsmatrix
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

void Shape::scale(float x,float y,float z){

    glm::mat4 matrix = glm::mat4{
        glm::vec4{x, 0.0f, 0.0f, 0.0f}, 
        glm::vec4{0.0f, y, 0.0f, 0.0f},
        glm::vec4{0.0f, 0.0f, z, 0.0f}, 
        glm::vec4{0.0f, 0.0f, 0.0f, 1.0f}};

    glm::inverse(glm::transpose(matrix)); 

    world_transformation_ *= matrix;
    world_transformation_inv_ = glm::inverse(world_transformation_);

    std::cout << "hello from scaled Shape.cpp \n";

}

void Shape::translate(float x,float y,float z){

    glm::mat4 matrix = glm::mat4{
        glm::vec4{1.0f, 0.0f, 0.0f, 0.0f}, 
        glm::vec4{0.0f, 1.0f, 0.0f, 0.0f},
        glm::vec4{0.0f, 0.0f, 1.0f, 0.0f}, 
        glm::vec4{x, y, z, 1.0f}};

    glm::inverse(glm::transpose(matrix)); 

    world_transformation_ *= matrix;
    world_transformation_inv_ = glm::inverse(world_transformation_);

    std::cout << "hello from translate Shape.cpp \n";
}

void Shape::rotate(float angle,float x,float y,float z){

    if(x == 1){
        glm::mat4 matrix = glm::mat4{
            glm::vec4{1.0f, 0.0f, 0.0f, 0.0f},
            glm::vec4{0.0f, cos(angle), -sin(angle), 0.0f},
            glm::vec4{0.0f,sin(angle),cos(angle),0.0f},
            glm::vec4{0.0f,0.0f,0.0f,1.0f}      
        };
    
        glm::inverse(glm::transpose(matrix)); 

        world_transformation_ *= matrix;
        world_transformation_inv_ = glm::inverse(world_transformation_);

    }
    
    if(y == 1){
        glm::mat4 matrix = glm::mat4{
            glm::vec4{sin(angle),0.0f,cos(angle),0.0f},
            glm::vec4{0.0f, 1.0f, 0.0f, 0.0f},
            glm::vec4{cos(angle), 0.0f, -sin(angle), 0.0f},
            glm::vec4{0.0f,0.0f,0.0f,1.0f}      
        };

        glm::inverse(glm::transpose(matrix)); 

        world_transformation_ *= matrix;
        world_transformation_inv_ = glm::inverse(world_transformation_);
    }
          
    if(z == 1){
           
        glm::mat4 matrix = glm::mat4{
            glm::vec4{cos(angle), -sin(angle), 0.0f, 0.0f},
            glm::vec4{sin(angle), cos(angle), 0.0f, 0.0f},
            glm::vec4{0.0f,0.0f,1.0f,0.0f},
            glm::vec4{0.0f,0.0f,0.0f,1.0f}      
        };

        glm::inverse(glm::transpose(matrix)); 

        world_transformation_ *= matrix;
        world_transformation_inv_ = glm::inverse(world_transformation_);
    }

    std::cout << "hello from rotate Shape.cpp \n";

}