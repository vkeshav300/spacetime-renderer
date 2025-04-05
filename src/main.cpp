#ifdef DEBUG
#warning "Debug mode enabled. This can cause heavy performance issues."
#endif

#include "objects/object.hpp"
#include "objects/shapes.hpp"
#include "renderer/engine.hpp"
#include "renderer/texture.hpp"

#include <simd/simd.h>

#include <memory>

int main() {
  std::shared_ptr<Camera> camera = std::make_shared<Camera>(
      vector_float3{0.0f, 0.0f, -5.0f}, vector_float3{0.0f, 0.0f, 0.0f},
      M_PI / 2, 1.0f, 100.0f);
  Engine engine(camera, 800, 600);

#ifdef DEBUG
  std::shared_ptr<Texture> texture = std::make_shared<Texture>(
      engine.get_device(), "assets/textures/test.jpg");
#else
  std::shared_ptr<Texture> texture = std::make_shared<Texture>(
      engine.get_device(), "../assets/textures/test.jpg");
#endif

  Object *obj = new Object(shapes::square);
  obj->set_texture(texture);
  obj->translate(0, 0, 2);
  obj->rotate(0, 0, 0, M_PI / 4);
  engine.add_object(obj);

  engine.stage();
  engine.render();
}