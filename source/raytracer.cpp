#include <renderer.hpp>
#include <window.hpp>

#include <GLFW/glfw3.h>
#include <thread>
#include <utility>
#include <cmath>
#include "scene.hpp"
#include "Sphere.hpp"
#include "Box.hpp"
#include "camera.hpp"
#include "light.hpp"

//now single threaded again
int main(int argc, char* argv[])
{
  unsigned const image_width = 800;
  unsigned const image_height = 600;
  std::string const filename = "./checkerboard.ppm";


  Scene sc_1{};    // Erstelle Raytracer-inhalte (Scene) welche im Renderer verarbeitet werden, Uebergabe mittels shared-pointer
  sc_1.ambient_light_ = 0.45f;
  Light li_1{"sun_1",{1.0f, 1.0f, 1.0f},{0.0f,0.0f,-20.0f}, 1.0f};
  auto ptr_li_1 = std::make_shared<Light>(li_1);
  sc_1.light_list_.push_back(ptr_li_1);
  // Illumination ill_1{};  // Grundbeleuchtung noch zu implement.

  Camera cam_1{"cam_1",{0.0f, 0.0f, 0.0f},{0.0f, 0.0f, -1.0f}, {0.0f, 0.0f, 1.0f}, 1.0f};
  auto ptr_cam_1 = std::make_shared<Camera>(cam_1);

  auto mix_green = std::make_shared<Material>(Material{"mix_green", {0.1f, 0.7f, 0.1f}, {0.1f, 0.7f, 0.1f}, {0.0f, 1.0f, 0.0f}, 5.0f});
  auto mix_blue = std::make_shared<Material>(Material{"mix_blue", {0.1f, 0.1f, 0.7f}, {0.1f, 0.1f, 0.7f}, {0.0f, 1.0f, 0.0f}, 5.0f});

  Sphere sp_1{"sp_1", mix_green, {5.0f, 0.0f, -45.0f}, 2.0f};
  auto ptr_sph_1 = std::make_shared<Sphere>(sp_1);

  Box bo_1{"bo_1", mix_blue, {10.0f,-10.0f,-110.0f}, {20.0f,10.0f,-80.0f}};
  auto ptr_bo_1 = std::make_shared<Box>(bo_1);

  sc_1.camera_ = ptr_cam_1;
  sc_1.shape_list.push_back(ptr_sph_1);
  sc_1.shape_list.push_back(ptr_bo_1);


  Renderer renderer{image_width, image_height, filename};

  //create separate thread to see updates of pixels while rendering
  //std::thread render_thread([&renderer]() {renderer.render();});
  renderer.render(sc_1);

  Window window{{image_width, image_height}};

  while (!window.should_close()) {
    if (window.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      window.close();
    }
    window.show(renderer.color_buffer());
  }

  //"join" threads, i.e. synchronize main thread with render_thread
  //render_thread.join();
  return 0;
}
