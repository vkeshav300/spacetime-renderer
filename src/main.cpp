#ifdef DEBUG
#warning "Debug mode enabled. This can cause heavy performance issues."
#endif

#include "objects/primitives/triangle.hpp"
#include "renderer/engine.hpp"

int main() {
  Engine engine(800, 600);

  Triangle *triangle = new Triangle();
  engine.add_object(triangle);

  engine.stage();
  engine.render();
}