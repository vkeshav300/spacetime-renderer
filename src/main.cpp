#ifdef DEBUG
#warning "Debug mode enabled. This can cause heavy performance issues."
#endif

#include "objects/primitives/square.hpp"
#include "renderer/engine.hpp"
#include "renderer/texture.hpp"

int main() {
  Engine engine(800, 600);

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