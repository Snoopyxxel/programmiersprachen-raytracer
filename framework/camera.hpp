#ifndef CAMERA_HPP
#define CAMERA_HPP
#include <glm/vec3.hpp>
#include <string>
#include <cmath>
#include "vec3_functions.hpp"

struct Camera{

    std::string name_;
    glm::vec3 pos_;
    glm::vec3 dir_;
    float fov_x_;
    glm::vec3 up_;

    Camera(const std::string &name, const glm::vec3 &pos, const glm::vec3 &dir, float fovX, const glm::vec3 &up)
            : name_(name), pos_(pos), dir_(dir), fov_x_(fovX), up_(up) {}

    friend std::ostream& operator<<(std::ostream& os, Camera const& cam)
	{
		os << "Name: " << cam.name_ 
			<< "; campos: " << cam.pos_
			<< "; camdir: " << cam.dir_
			<< "; fov: " << cam.fov_x_
            << "; camup: " << cam.up_;
		return os;
	}
};

#endif
