#ifdef DEBUG
#warning "Debug mode enabled. This can cause heavy performance issues."
#endif

#include "objects/primitives/square.hpp"
#include "renderer/engine.hpp"
#include "renderer/texture.hpp"

#include <cmath>

int main() {
  Camera *camera =
      new Camera(vector_float3{0.0f, -5.0f, 0.0f},
                 vector_float3{0.0f, 0.0f, 0.0f}, M_PI / 2, 1.0f, 100.0f);
  Engine engine(camera, 800, 600);

#ifdef DEBUG
  Texture *texture =
      new Texture(engine.get_device(), "assets/textures/test.jpg");
#else
  Texture *texture =
      new Texture(engine.get_device(), "../assets/textures/test.jpg");
#endif

  Square *shape = new Square();
  shape->set_texture(texture);
  engine.add_object(shape);

  engine.stage();
  engine.render();
}