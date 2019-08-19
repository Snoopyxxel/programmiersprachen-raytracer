#include "Triangle.hpp"
#include <glm/vec3.hpp>
#include <cmath>
#include <iostream>


Triangle::Triangle() :      // default-constr-Sphere
        Shape(),    // hier uebertragung des Strings "Box" in die Basisklasse als name-parameter
        e1_ {0.0f, 0.0f, 0.0f},
        e2_ {0.0f, 5.0f, 0.0f},
        e3_ {0.0f, 0.0f, 5.0f}{/* std::cout << "I am the Triangle-contructor !";*/}
/*
Triangle::Triangle(glm::vec3 const& min,glm::vec3 const& max) :   // custom-constr-Sphere 2 param
  Shape::Shape{"Triangle"},
  min_ {min},
  max_ {max}{/* std::cout << "I am the Triangle-contructor !";*/ //}
/*
Triangle::Triangle(glm::vec3 const& min,glm::vec3 const& max,std::string name, std::shared_ptr<Material> const& ma_co) :  // custom-constr-Sphere 4 param
  Shape::Shape{name,ma_co},  // Parameter werden weitergereicht an den konstr der basisklasse für die entspr. parameter
  min_ {min},
  max_ {max}{/* std::cout << "I am the Triangle-contructor !";*/ //}

Triangle::~Triangle(){
    //std::cout << "I am the Triangle-Destruktor !";
}


float Triangle::area() const {        // Formel checken !!!
    //if((min_.x > max_.x) || (min_.y > max_.y) || (min_.z > max_.z)){
    //  std::cout << "\nyour min and max values are incorrect !\n";
    return 1.0f;
}

float Triangle::volume() const {  // Formel checken !!!
    //if((min_.x > max_.x) || (min_.y > max_.y) || (min_.z > max_.z)){
    //  std::cout << "\nyour min and max values are incorrect !\n";
    return 0.0f;
}

HitPoint Triangle::intersect(Ray & ray) const{
    HitPoint h1;
    return h1;
}

std::ostream& Triangle::print(std::ostream& os) const {
    Shape::print(os); // print methode der basisklasse wir mit augerufen -für basis attributausgabe
    return os;
    /*return os << "Minimum : " << min_.x << "\t" << min_.y << "\t" << min_.z << "\n"
       << "Maximum : " << max_.x << "\t" << max_.y << "\t" << max_.z << "\n";*/
}

Triangle::Triangle(const glm::vec3 &e1, const glm::vec3 &e2, const glm::vec3 &e3) : e1_(e1), e2_(e2), e3_(e3) {}

