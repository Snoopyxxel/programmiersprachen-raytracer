#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "Box.hpp"
#include "Sphere.hpp"
#include <glm/glm.hpp>
#include "vec3_functions.hpp"
#include <glm/gtx/intersect.hpp>
#include <scene.hpp>
#include "camera.hpp"
#include "light.hpp"

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
    Color red_c{255, 0, 0};
    auto red = std::make_shared<Material>("red", red_c, red_c, red_c, 1);
    auto sphere = std::make_shared<Sphere>(Sphere{"Sphere1", red, {0,0,0}, 1});
    s = sphere;
    s->print();
    std::cout << *s;
    sphere->print();

    std::cout << "\n\n";

    auto box = std::make_shared<Box>(Box{"Box1", red,{0,0,0},{1,1,1}});
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
    Color red_c{255, 0, 0};
    auto red = std::make_shared<Material>("red", red_c, red_c, red_c, 1);
    Sphere sphere{"test_sphere", red, {0.0f, 0.0f, 5.0f}, 1.0f};
    auto result = sphere.intersect(ray);
    REQUIRE(result.intersected);
    REQUIRE(result.material->ka.r == red_c.r);
    REQUIRE(result.name == "test_sphere");
    REQUIRE(result.distance == 4.0f);
    REQUIRE(result.intersection_point == glm::vec3(0.0f, 0.0f, 4.0f));
    REQUIRE(result.intersection_ray_direction == glm::vec3(0.0f, 0.0f, 1.0f));
}

TEST_CASE("intersect box"){
    std::set<float> test;
    test.insert(5.0f);

    Color red_c{255, 0, 0};
    auto red = std::make_shared<Material>("red", red_c, red_c, red_c, 1);
    Box box1{"box1", red, {0, 0, 0}, {1, 1, 1}};
    Ray ray1{{0.5f, 0.5f, -1.0f}, {0.0f,0.0f,1.0f}};
    auto result1 = box1.intersect(ray1);
    float test_intersect;
    REQUIRE(glm::intersectRayPlane(glm::vec3{0, 0, 0}, glm::vec3{0, 0, -1}, glm::vec3{0, 0, 1}, glm::vec3{0, 0, 1}, test_intersect));
    std::cout << test_intersect;
    REQUIRE(result1.intersected);
    REQUIRE(result1.intersection_point == glm::vec3(0.5f, 0.5f, 0.0f));
}

TEST_CASE("TestCase_7   sdf_files  aufg 6.5 ","[aufgabe 6.5]") {
}

TEST_CASE("Scene test") {

    std::cout << "\n\nScene-Content-Test\n\n";
    std::shared_ptr<Scene> sc_1 = std::make_shared<Scene>(); //erzeugt Zeiger auf Scene-objekt (struct)
    get_SDF_File("/scene/scene_1.sdf",*sc_1);  // einlesen d pfades als string, derefer. zeiger auf scene-objekt
    std::cout<<"search_mat_printout \n:"<<*search_map("red",*sc_1)<<"\n"; // liefert zeiger zurück, daher noch dereferenz vor print
    REQUIRE(search_map("black",*sc_1)==nullptr); // ausnahmefall wenn keine uebereinstimmung gefunden

    //std::cout << "\nthe ambient_light_ of this scene is" << sc_1.ambient_light_; // warum hier kein direkter zugriff auf attr auch bei public nicht mgl.?
    std::cout << "\nthe ambient_light_ of this scene is:    " << get_ambient_light_(*sc_1);
    std::cout << "\nHello team-raytracer \n"; 
/*
  std::shared_ptr<Scene> sc_2 = std::make_shared<Scene>(); //erzeugt Zeiger auf Scene-objekt (struct)
	get_SDF_File("/home/simon/Desktop/scene_1.sdf",*sc_2);  // einlesen d pfades als string, derefer. zeiger auf scene-objekt
  std::cout<<"search_vec_printout :"<<*search_vec("red",*sc_2)<<"\n"; // liefert zeiger zurück, daher noch dereferenz vor print
  REQUIRE(search_mat("black",*sc_2)==nullptr); // ausnahmefall wenn keine uebereinstimmung gefunden
 
  std::shared_ptr<Scene> sc_3 = std::make_shared<Scene>(); //erzeugt Zeiger auf Scene-objekt (struct)
	get_SDF_File("/home/simon/Desktop/scene_1.sdf",*sc_3);  // einlesen d pfades als string, derefer. zeiger auf scene-objekt
  std::cout<<"search_set_printout :"<<*search_set("red",*sc_3)<<"\n"; // liefert zeiger zurück, daher noch dereferenz vor print
  REQUIRE(search_mat("black",*sc_3)==nullptr); // ausnahmefall wenn keine uebereinstimmung gefunden
*/

}

TEST_CASE("TestCase_test   camera.hpp and light.hpp as  structs ok  ","[7xx]") {

    glm::vec3 test_vec{0.0f, 0.0f, 1.0f};
 //   Camera cam_1{"cam1",test_vec,test_vec,test_vec,test_vec};
    std::cout << "Hello cam1 \n"; 
 //   std::cout << cam_1;

    std::cout << "Hello sun \n"; 
    glm::vec3 test_vec_sun{1.0f, 1.0f, 1.0f};
    Color co_sun{255,255,255};
    Light li_1{"sun_1",test_vec_sun,co_sun,0.5f};
    std::cout << li_1;

}

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
