#ifndef RAYTRACER_MATERIAL_HPP
#define RAYTRACER_MATERIAL_HPP


#include <string>
#include <ostream>
#include "color.hpp"

struct Material {
    std::string name;
    Color ka;
    Color kd;
    Color ks;
    float m;

    friend std::ostream &operator<<(std::ostream &os, const Material &material);

    Material(const std::string &name, const Color &ka, const Color &kd, const Color &ks, float m);
};


#endif //RAYTRACER_MATERIAL_HPP
