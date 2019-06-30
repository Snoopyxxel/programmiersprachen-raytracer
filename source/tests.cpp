#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "Box.hpp"
#include "Sphere.hpp"
#include <glm/glm.hpp>
#include "vec3_functions.hpp"
#include <glm/gtx/intersect.hpp>

TEST_CASE("area box", "[box]"){
    Box a{{5.0f, 5.0f, 2.0f}, {9.0f,9.0f,3.0f}};
    Box b{{0,0,0}, {1,1,1}};
    Box c{{-5.0f, -5.0f, -2.0f}, {9.0f,9.0f,3.0f}};
    REQUIRE(a.area() == 48);
    REQUIRE(b.area() == 6);
    REQUIRE(c.area() == 672);
}

TEST_CASE("volume box", "[box]"){
    Box a{{5.0f, 5.0f, 2.0f}, {9.0f,9.0f,3.0f}};
    Box b{{0,0,0}, {1,1,1}};
    Box c{{-5.0f, -5.0f, -2.0f}, {9.0f,9.0f,3.0f}};
    REQUIRE(a.volume() == 16);
    REQUIRE(b.volume() == 1);
    REQUIRE(c.volume() == 980);
}

TEST_CASE("volume sphere", "[sphere]"){
    Sphere a{{0, 0, 0}, 5};
    Sphere b{{10, -3, -7}, 3};

    REQUIRE(a.volume() == Approx(523.5987755983));
    REQUIRE(b.volume() == Approx(113.09733552923));
}

TEST_CASE("area sphere", "[sphere]"){
    Sphere a{{0, 0, 0}, 5};
    Sphere b{{10, -3, -7}, 3};

    REQUIRE(a.area() == Approx(314.15926535898));
    REQUIRE(b.area() == Approx(113.09733552923));
}

TEST_CASE("shape"){
    std::shared_ptr<Shape> s;
    auto sphere = std::make_shared<Sphere>(Sphere{{0,0,0}, 1});
    s = sphere;
    REQUIRE(s->area() == Approx(12.566370614359));
    REQUIRE(s->volume() == Approx(4.1887902047864));
}

TEST_CASE("print shape"){
    std::shared_ptr<Shape> s;
    auto sphere = std::make_shared<Sphere>(Sphere{"Sphere1", {1,0,0},{0,0,0}, 1});
    s = sphere;
    s->print();
    std::cout << *s;
    sphere->print();

    std::cout << "\n\n";

    auto box = std::make_shared<Box>(Box{"Box1", {1,0,0},{0,0,0},{1,1,1}});
    s = box;
    s->print();
    std::cout << *s;
    box->print();
}

TEST_CASE("intersect_ray_sphere" , "[intersect]"){
// Ray
    glm::vec3 ray_origin{0.0f, 0.0f, 0.0f};
// ray direction has to be normalized !
// you can use :
// v = glm::normalize(some_vector)
    glm::vec3 ray_direction{0.0f, 0.0f, 1.0f};
// Sphere
    glm::vec3 sphere_center{0.0f, 0.0f, 5.0f};
    float sphere_radius{1.0f};
    float distance = 0.0f;
    auto result = glm::intersectRaySphere(ray_origin, ray_direction, sphere_center, sphere_radius * sphere_radius, distance); // squared radius !!!
    REQUIRE(distance == Approx(4.0f));
}

TEST_CASE("intersect sphere"){
    Ray ray{{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}};
    Color red{255, 0, 0};
    Sphere sphere{"test_sphere", red, {0.0f, 0.0f, 5.0f}, 1.0f};
    auto result = sphere.intersect(ray);
    REQUIRE(result.intersected);
    REQUIRE(result.color.r == 255);
    REQUIRE(result.name == "test_sphere");
    REQUIRE(result.distance == 4.0f);
    REQUIRE(result.intersection_point == glm::vec3(0.0f, 0.0f, 4.0f));
    REQUIRE(result.intersection_ray_direction == glm::vec3(0.0f, 0.0f, 1.0f));
}


int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
