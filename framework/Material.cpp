#include "Material.hpp"

std::ostream &operator<<(std::ostream &os, const Material &material) {
    os << "{ Name: " << material.name << ", ka: " << material.ka << ", kd: " << material.kd << ", ks: " << material.ks
       << ", m: " << material.m << " }";
    return os;
}

Material::Material(const std::string &name, const Color &ka, const Color &kd, const Color &ks, float m) : name(name),
                                                                                                          ka(ka),
                                                                                                          kd(kd),
                                                                                                          ks(ks),
                                                                                                          m(m) {}
