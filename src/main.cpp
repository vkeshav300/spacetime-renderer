#include "renderer/camera.h"
#include "renderer/engine.h"

#include "objects/cube.h"

#include <cmath>

int main(int argc, char *argv[]) {

  Camera *camera = new Camera(vector_float3{0, 0, -5}, vector_float3{0, 0, 0},
                              M_PI / 2, 1.0f, 50.0f);

  Engine engine(800, 600, camera, 4);

  Cube *cube = new Cube(vector_float3{0, 0, 0}, 0, vector_float3{0, 0, 0});

  cube->m_texture =
      new Texture(engine.get_device(), "../assets/textures/test.jpeg");

  engine.add_object(cube);

  engine.stage();
  engine.render();

  return 0;
}
