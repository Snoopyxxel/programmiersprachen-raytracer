#ifndef RAYTRACER_VEC3_FUNCTIONS_HPP
#define RAYTRACER_VEC3_FUNCTIONS_HPP

#include <ostream>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

std::ostream &operator<<(std::ostream &os, const glm::vec3 &vec);

bool operator==(const glm::vec3 &a, const glm::vec3 &b);

glm::vec3 transform(glm::vec3 const& vec3, glm::mat4 const& mat4, float w);
#endif