#include "Shape.hpp"
#include <glm/vec3.hpp>

#ifndef RAYTRACER_BOX_HPP
#define RAYTRACER_BOX_HPP


class Box : public Shape {
public:

    Box(const glm::vec3 &min, const glm::vec3 &max);

    Box(const std::string &name, const Color &color, const glm::vec3 &min, const glm::vec3 &max);

    float area() const override;

    float volume() const override;

private:
    glm::vec3 min_;
    glm::vec3 max_;
};


#endif //RAYTRACER_BOX_HPP
