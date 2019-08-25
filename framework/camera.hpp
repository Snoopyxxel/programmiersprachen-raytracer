#ifndef CAMERA_HPP
#define CAMERA_HPP
#include <glm/vec3.hpp>
#include <string>
#include <cmath>

struct Camera{

    std::string name_;
    glm::vec3 campos_;
    glm::vec3 camdir_;
    glm::vec3 camright_;
    unsigned int f_Of_V_;

    Camera(std::string name, glm::vec3 campos, glm::vec3 camdir, glm::vec3 camright, unsigned int f_Of_V):
    name_(name), campos_(campos), camdir_(camdir), camright_(camright), f_Of_V_(f_Of_V){}

    friend std::ostream& operator<<(std::ostream& os, Camera const& cam)
	{
		os << "Name: " << cam.name_ 
			<< ", campos: (" << cam.campos_.x << ", " << cam.campos_.y << ", " << cam.campos_.z 
			<< "), camdir: (" << cam.camdir_.x << ", " << cam.camdir_.y << ", " << cam.camdir_.z 
			<< "), camright: (" << cam.camright_.x << ", " << cam.camright_.y << ", " << cam.camright_.z 
           // << "), camdown: (" << f_Of_V_
			<< "), Öffnungswinkel Fov noch nicht implementiert: " << "\n";
		return os;
	}
};

#endif
