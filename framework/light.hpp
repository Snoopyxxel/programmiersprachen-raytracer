#ifndef LIGHT_HPP
#define LIGHT_HPP
#include "color.hpp"
#include <glm/vec3.hpp>


struct Light{


    std::string name_;
    Color col_;
    glm::vec3 pos_;
    double luminosity_;

    Light(std::string name, glm::vec3 lightpos, Color col, double luminosity):
    name_(name), pos_(lightpos), col_(col), luminosity_(luminosity){}

    friend std::ostream& operator<<(std::ostream& os, Light const& li){
        os << " name: " << li.name_
            << ", pos: " << li.pos_.x << ", " << li.pos_.y << ", " << li.pos_.z
            << ", color: " << li.col_
            << ", luminosity: " << li.luminosity_ << std::endl;
        return os;
    }

};



#endif