#pragma once

#include "../../renderer/gpu_buffers.h"
#include "object_i.hpp"

#include <array>

class Triangle : public Object_I<Triangle> {
protected:
  std::array<Vertex, 3> m_vertices = {
      {{{-0.5f, -0.5f, 0.0f, 1.0f}, {0.0f, 0.0f}},
       {{0.5f, -0.5f, 0.0f, 1.0f}, {0.0f, 0.0f}},
       {{0.0f, 0.5f, 0.0f, 1.0f}, {0.0f, 0.0f}}}};

  Texture *m_texture;

  friend class Object_I<Triangle>;

public:
  Triangle();
  ~Triangle();
};