#ifndef RAYTRACER_MATERIAL_HPP
#define RAYTRACER_MATERIAL_HPP


#include <string>
#include <ostream>
#include "color.hpp"

struct Material {
    std::string name;
    Color ka;  // Reflexionsfaktor für ambientes Licht
    Color kd;  // Reflexionsfaktor für diffuses Licht
    Color ks;  // Reflexionsfaktor für spiegelndes Licht
    float m;   // Exponent zur Beschreibung der Oberflächenbeschaffenheit

    friend std::ostream &operator<<(std::ostream &os, const Material &material);

    Material(const std::string &name, const Color &ka, const Color &kd, const Color &ks, float m);
};


#endif //RAYTRACER_MATERIAL_HPP
