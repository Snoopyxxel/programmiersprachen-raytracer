#ifndef RAYTRACER_SHAPE_HPP
#define RAYTRACER_SHAPE_HPP


#include <string>
#include <ostream>
#include "color.hpp"
#include "ray.hpp"
#include "hitpoint.hpp"
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <memory>

class Shape {
public:
    Shape();
    Shape(std::string const &name, std::shared_ptr<Material> const& material);

    virtual float area() const = 0;
    virtual float volume() const = 0;

    friend std::ostream &operator<<(std::ostream &os, const Shape &shape);

    virtual HitPoint intersect(Ray const& ray) const = 0;

    virtual std::ostream& print(std::ostream &os = std::cout) const;

    virtual glm::vec3 normal(glm::vec3 const& p) const = 0;   //point has to be on the object!


    void scale(float x,float y,float z);

    void translate(float x,float y,float z);

    void rotate(float angle,float x,float y,float z);



    std::string get_name();
    

protected:
    
    std::string name_;
    std::shared_ptr<Material> material_;
    glm::mat4 world_transformation_;
    glm::mat4 world_transformation_inv_;
};


#endif //RAYTRACER_SHAPE_HPP
