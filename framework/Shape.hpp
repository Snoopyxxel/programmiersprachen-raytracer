#ifndef RAYTRACER_SHAPE_HPP
#define RAYTRACER_SHAPE_HPP


#include <string>
#include <ostream>
#include "color.hpp"
#include "ray.hpp"
#include "hitpoint.hpp"
#include <glm/vec3.hpp>
#include <memory>

class Shape {
public:
    Shape();
    Shape(std::string const &name, std::shared_ptr<Material> const& material);

    virtual float area() const = 0;
    virtual float volume() const = 0;

    friend std::ostream &operator<<(std::ostream &os, const Shape &shape);

    virtual HitPoint intersect(Ray &ray) const = 0;

    virtual std::ostream& print(std::ostream &os = std::cout) const;

protected:
    std::string name_;
    std::shared_ptr<Material> material_;
};


#endif //RAYTRACER_SHAPE_HPP
