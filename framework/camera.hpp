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
    name_(name), campos_(pos), camdir_(camdir), camright_(camright), camdown_(camdown){


#endif
