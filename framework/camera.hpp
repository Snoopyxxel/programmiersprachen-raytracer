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
    glm::vec3 camdown_;

    Camera(std::string name, glm::vec3 campos, glm::vec3 camdir, glm::vec3 camright, glm::vec3 camdown):
    name_(name), campos_(campos), camdir_(camdir), camright_(camright), camdown_(camdown){}

    friend std::ostream& operator<<(std::ostream& os, Camera const& cam)
	{
		os << "Name: " << cam.name_ 
			<< ", campos: (" << cam.campos_.x << ", " << cam.campos_.y << ", " << cam.campos_.z 
			<< "), camdir: (" << cam.camdir_.x << ", " << cam.camdir_.y << ", " << cam.camdir_.z 
			<< "), camright: (" << cam.camright_.x << ", " << cam.camright_.y << ", " << cam.camright_.z 
            << "), camdown: (" << cam.camdown_.x << ", " << cam.camdown_.y << ", " << cam.camdown_.z 
			<< "), Öffnungswinkel Fov noch nicht implementiert: " << "\n";
		return os;
	}
};

#endif
