#ifndef RAYTRACER_VEC3_FUNCTIONS_HPP
#define RAYTRACER_VEC3_FUNCTIONS_HPP

#include <ostream>
#include <glm/vec3.hpp>

std::ostream &operator<<(std::ostream &os, const glm::vec3 &vec);

bool operator==(const glm::vec3 &a, const glm::vec3 &b);

#endif