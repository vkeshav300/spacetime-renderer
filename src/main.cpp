#ifdef DEBUG
#warning "Debug mode enabled. This can cause heavy performance issues."
#endif

#include "objects/primitives/square.hpp"
#include "renderer/engine.hpp"
#include "renderer/texture.hpp"

#include <simd/simd.h>

#include <cmath>
#include <memory>

int main() {
  std::shared_ptr<Camera> camera = std::make_shared<Camera>(
      vector_float3{0.0f, 0.0f, -5.0f}, vector_float3{0.0f, 0.0f, 0.0f},
      M_PI / 2, 0.1f, 10.0f);
  Engine engine(camera, 800, 600);

#ifdef DEBUG
  std::shared_ptr<Texture> texture = std::make_shared<Texture>(
      engine.get_device(), "assets/textures/test.jpg");
#else
  std::shared_ptr<Texture> texture = std::make_shared<Texture>(
      engine.get_device(), "../assets/textures/test.jpg");
#endif

  Square *shape = new Square();
  shape->set_texture(texture);
  shape->translate(0, 0, 2);
  engine.add_object(shape);

  engine.stage();
  engine.render();
}