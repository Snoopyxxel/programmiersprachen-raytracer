#ifndef RAYTRACER_SHAPE_HPP
#define RAYTRACER_SHAPE_HPP


#include <string>
#include "color.hpp"

class Shape {
public:
    Shape(const std::string &name = "", const Color &color = {1,1,1});

    virtual float area() const = 0;
    virtual float volume() const = 0;
private:
    std::string name_;
    Color color_;
};


#endif //RAYTRACER_SHAPE_HPP
