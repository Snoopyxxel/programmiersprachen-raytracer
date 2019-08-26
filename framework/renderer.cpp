// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#include "renderer.hpp"
#include "ray.hpp"
#include "scene.hpp"
#include "illumination.hpp"

Renderer::Renderer(unsigned w, unsigned h, std::string const& file)
  : width_(w)
  , height_(h)
  , color_buffer_(w*h, Color{0.0, 0.0, 0.0})
  , filename_(file)
  , ppm_(width_, height_)
{}

void Renderer::render(Scene const& scene) {
  std::size_t const checker_pattern_size = 20;
  float d = (float(width_) / 2.0f) / (tanf(scene.camera_->fov_x_ / 2.0f));

  Color background_color{0.5f, 0.5f, 1.0f};

  for (unsigned y = 0; y < height_; ++y) {
    for (unsigned x = 0; x < width_; ++x) {
      Pixel p(x,y);
      Ray ray{scene.camera_->pos_, {x-(float(width_) / 2.0f), y - (float(height_) / 2.0f), -d}};
      ray.direction = glm::normalize(ray.direction);

      p.color = background_color;
      HitPoint closest_i{false, std::numeric_limits<float>::infinity()};
      for (auto const& obj : scene.shape_list){
          HitPoint intersection = obj->intersect(ray);
          if (intersection.intersected and intersection.distance < closest_i.distance){
              closest_i = intersection;
              auto closest_o = obj;
              if (closest_i.intersected){
                  p.color = phong(ray, intersection, obj, scene);
              } else{
                  p.color = background_color;
              }
          }
      }
      /*
      if ( ((x/checker_pattern_size)%2) != ((y/checker_pattern_size)%2)) {
        p.color = Color{0.0f, 1.0f, float(x)/height_};
      } else {
        p.color = Color{1.0f, 0.0f, float(y)/width_};
      }
      */
      write(p);
    }
  }
  ppm_.save(filename_);
}

void Renderer::write(Pixel const& p)
{
  // flip pixels, because of opengl glDrawPixels
  size_t buf_pos = (width_*p.y + p.x);
  if (buf_pos >= color_buffer_.size() || (int)buf_pos < 0) {
    std::cerr << "Fatal Error Renderer::write(Pixel p) : "
      << "pixel out of ppm_ : "
      << (int)p.x << "," << (int)p.y
      << std::endl;
  } else {
    color_buffer_[buf_pos] = p.color;
  }

  ppm_.write(p);
}
