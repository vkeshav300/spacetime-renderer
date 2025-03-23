#pragma once

#include "../../renderer/gpu_buffers.h"
#include "object_i.hpp"

#include <array>

class Triangle : public Object_I<Triangle> {
private:
  std::array<Vertex, 3> m_verticies = {
      {{{-0.5f, -0.5f, 0.0f, 1.0f}, {0.0f, 0.0f}},
       {{0.5f, -0.5f, 0.0f, 1.0f}, {0.0f, 0.0f}},
       {{0.0f, 0.5f, 0.0f, 1.0f}, {0.0f, 0.0f}}}};

  Texture *m_texture;

  vector_float3 m_translations = {0.0f, 0.0f, 0.0f};
  vector_float4 m_rotations = {0.0f, 0.0f, 0.0f, 0.0f};

  friend class Object_I<Triangle>;

public:
  Triangle();
  ~Triangle();
};