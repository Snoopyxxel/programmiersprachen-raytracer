#ifndef RAYTRACER_ILLUMINATION_HPP
#define RAYTRACER_ILLUMINATION_HPP

#include <glm/vec3.hpp>
#include "ray.hpp"
#include "hitpoint.hpp"
#include "Shape.hpp"
#include "scene.hpp"

bool check_obstruction(glm::vec3 const& p1, glm::vec3 const& p2);
Color phong(Ray const& ray, HitPoint const& intersection, std::shared_ptr<Shape> const& inters_o, Scene const& scene);



#endif //RAYTRACER_ILLUMINATION_HPP
