#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "Box.hpp"
#include "Sphere.hpp"

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


int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
