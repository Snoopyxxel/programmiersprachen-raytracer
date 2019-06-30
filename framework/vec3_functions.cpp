#include "vec3_functions.hpp"

std::ostream &operator<<(std::ostream &os, const glm::vec3 &vec) {
    os << "(" << vec.x << " | " << vec.y << " | "<< vec.z << ")";
    return os;
}

bool operator==(const glm::vec3 &a, const glm::vec3 &b){
    return (a.x == b.x and a.y == b.y and a.z == b.z);
}
