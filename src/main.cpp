#ifdef DEBUG // Debug mode can be a performance killer
#warning "Debug mode is enabled"
#endif

#include "renderer/camera.h"
#include "renderer/engine.h"

#include "objects/primitives/cube.h"

#include <cmath>

int main(int argc, char *argv[]) {

  Camera *camera = new Camera(vector_float3{0, 0, -5}, vector_float3{0, 0, 0},
                              M_PI / 2, 1.0f, 50.0f);

  Engine engine(800, 600, camera, 4);

  Cube *cube = new Cube(vector_float3{0, 0, -10}, 0, vector_float3{0, 0, 0});

#ifdef DEBUG
  cube->set_texture(
      new Texture(engine.get_device(), "assets/textures/test.jpeg"));
#else
  cube->set_texture(
      new Texture(engine.get_device(), "../assets/textures/test.jpeg"));
#endif

  engine.add_object(cube);

  engine.stage();
  engine.render();

  return 0;
}
