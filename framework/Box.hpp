#ifndef RAYTRACER_BOX_HPP
#define RAYTRACER_BOX_HPP

#include "Shape.hpp"
#include <glm/vec3.hpp>

class Box : public Shape {
public:

    Box(const glm::vec3 &min, const glm::vec3 &max);

    Box(const std::string &name, const std::shared_ptr<Material> &material, const glm::vec3 &min, const glm::vec3 &max);

    float area() const override;

    float volume() const override;

    std::ostream& print(std::ostream &os = std::cout) const override;

    HitPoint intersect(Ray const& ray) const override;

    glm::vec3 normal(glm::vec3 const& p) const override;

    void scale(float x, float y, float z) const override;

    void translate(float x, float y, float z) const override;

    void rotate(float angle, float x, float y, float z) const override;

private:
    glm::vec3 min_;
    glm::vec3 max_;
};


#endif //RAYTRACER_BOX_HPP
