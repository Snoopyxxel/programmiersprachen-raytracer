#ifndef RAYTRACER_SHAPE_HPP
#define RAYTRACER_SHAPE_HPP


#include <string>
#include <ostream>
#include "color.hpp"
#include "ray.hpp"
#include "hitpoint.hpp"
#include <glm/vec3.hpp>

class Shape {
public:
    Shape(std::string const &name = "", const Color &color = {1,1,1});

    virtual float area() const = 0;
    virtual float volume() const = 0;

    friend std::ostream &operator<<(std::ostream &os, const Shape &shape);

    virtual HitPoint intersect(Ray &ray) const = 0;

    virtual std::ostream& print(std::ostream &os = std::cout) const;

protected:
    std::string name_;
    Color color_;
};


#endif //RAYTRACER_SHAPE_HPP
