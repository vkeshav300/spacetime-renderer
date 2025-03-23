#pragma once

#include "../../renderer/gpu_buffers.h"
#include "object_i.hpp"

#include <array>

class Triangle : public Object_I<Triangle> {
private:
  std::array<Vertex, 3> m_verticies;

  Texture *m_texture;

  friend class Object_I<Triangle>;

public:
  Triangle();
  ~Triangle();
};