#include "Box.hpp"
#include "vec3_functions.hpp"
#include <stdexcept>
#include <glm-0.9.5.3/glm/gtx/intersect.hpp>
#include <vector>
#include <set>

Box::Box(const glm::vec3 &min, const glm::vec3 &max) : Shape(), min_(min), max_(max) {
    if(min.x >= max.x or min.y >= max.y or min.z >= max.z){
        throw std::invalid_argument("min should be smaller than max in every coordinate!");
    }
}

float Box::area() const {
    float breite = abs(min_.z - max_.z);
    float tiefe = abs(min_.x - max_.x);
    float hoehe = abs(min_.y - max_.y);
    return 2 * (breite * tiefe + breite * hoehe + tiefe * hoehe);
}

float Box::volume() const {
    float breite = abs(min_.z - max_.z);
    float tiefe = abs(min_.x - max_.x);
    float hoehe = abs(min_.y - max_.y);
    return breite * hoehe * tiefe;
}

Box::Box(const std::string &name, const std::shared_ptr<Material> &material, const glm::vec3 &min, const glm::vec3 &max) : Shape(name, material), min_(min), max_(max) {}

std::ostream& Box::print(std::ostream &os) const {
    Shape::print(os);
    os << "; Minimum: " << min_ << "; Maximum: " << max_ << std::endl;
    return os;
}

HitPoint Box::intersect(Ray const& ray) const {

    float tmin = (min_.x - ray.origin.x) / ray.direction.x;
    float tmax = (max_.x - ray.origin.x) / ray.direction.x;

    if (tmin > tmax) std::swap(tmin, tmax);

    float tymin = (min_.y - ray.origin.y) / ray.direction.y;
    float tymax = (max_.y - ray.origin.y) / ray.direction.y;

    if (tymin > tymax) std::swap(tymin, tymax);

    if ((tmin > tymax) || (tymin > tmax))
        return HitPoint{false, std::numeric_limits<float>::infinity()};

    if (tymin > tmin)
        tmin = tymin;

    if (tymax < tmax)
        tmax = tymax;

    float tzmin = (min_.z - ray.origin.z) / ray.direction.z;
    float tzmax = (max_.z - ray.origin.z) / ray.direction.z;

    if (tzmin > tzmax) std::swap(tzmin, tzmax);

    if ((tmin > tzmax) || (tzmin > tmax))
        return HitPoint{false, std::numeric_limits<float>::infinity()};

    if (tzmin > tmin)
        tmin = tzmin;


    /*
    if (tzmax < tmax)
        tmax = tzmax;

    if (tmax < tmin) std::swap(tmax, tmin);


    if (tmin < 0.00005){
        return HitPoint{false, std::numeric_limits<float>::infinity()};
    }
     */

    return HitPoint{true, tmin, name_, material_, ray.origin + tmin * ray.direction, ray.direction};



    /*
    Ray ray1 = {ray.origin, -ray.direction};

    ray1.direction = glm::normalize(ray1.direction);

    float distance[6];
    bool face_intersect[6];
    std::set<float> checked_distance;


    face_intersect[0] = glm::intersectRayPlane(ray1.origin, ray1.direction, min_, glm::vec3{0, 0, 1}, distance[0]); // x, y plane
    face_intersect[1] = glm::intersectRayPlane(ray1.origin, ray1.direction, min_, glm::vec3{0, 1, 0}, distance[1]); // x, z plane
    face_intersect[2] = glm::intersectRayPlane(ray1.origin, ray1.direction, min_, glm::vec3{1, 0, 0}, distance[2]); // y, z plane
    face_intersect[3] = glm::intersectRayPlane(ray1.origin, ray1.direction, max_, glm::vec3{0, 0, 1}, distance[3]);
    face_intersect[4] = glm::intersectRayPlane(ray1.origin, ray1.direction, max_, glm::vec3{0, 1, 0}, distance[4]);
    face_intersect[5] = glm::intersectRayPlane(ray1.origin, ray1.direction, max_, glm::vec3{1, 0, 0}, distance[5]);

    for(int i = 0; i < 6; ++i){
        if(face_intersect[i]){
            glm::vec3 intersection = ray.origin + -distance[i] * ray.direction;
            if(intersection.x >= min_.x and intersection.x <= max_.x and intersection.y >= min_.y and intersection.y <= max_.y and intersection.z >= min_.z and intersection.z <= max_.z){
                checked_distance.insert(-distance[i]);
            }
        }
    }

    std::string name = "";
    Color color = {-1, -1, -1};
    auto material = std::make_shared<Material>("no_color", color, color, color, -1);
    bool result = false;
    if(*checked_distance.begin() != 0){
        name = name_;
        material = material_;
        result = true;
    }

    return HitPoint{result, *checked_distance.begin(), name, material, ray.origin + *checked_distance.begin() * ray.direction, ray.direction};
     */
}

glm::vec3 Box::normal(glm::vec3 const& p) const {

    if (fabsf(p.y - min_.y) < 0.0005f){
        return {0.0f, -1.0f, 0.0f};
    }
    if (fabsf(p.y - max_.y) < 0.0005f){
        return {0.0f, 1.0f, 0.0f};
    }

    if (fabsf(p.x - min_.x) < 0.0005f){
        return {-1.0f, 0.0f, 0.0f};
    }
    if (fabsf(p.x - max_.x) < 0.0005f){
        return {1.0f, 0.0f, 0.0f};
    }

    if (fabsf(p.z - min_.z) < 0.0005f){
        return {0.0f, 0.0f, -1.0f};
    }
    if (fabsf(p.z - max_.z) < 0.0005f){
        return {0.0f, 0.0f, 1.0f};
    }

}

//void Box::scale(float x, float y, float z) const{}

//void Box::translate(float x, float y, float z) const {}

//void Box::rotate(float angle, float x, float y, float z) const {}
