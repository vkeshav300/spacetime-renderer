#pragma once

#include "../../renderer/texture.h"
#include "data.h"
#include "object_i.h"

#include <array>

#include <Metal/Metal.hpp>
#include <simd/simd.h>

class Cube : public Object_I<Cube> {
protected:
  static constexpr MTL::PrimitiveType m_prim_type = MTL::PrimitiveTypeTriangle;
  static constexpr size_t m_vertex_start = 0;

  std::array<Vertex, 36> m_verticies;
  Transformations m_transformations;

  Texture *m_texture = nullptr;

  friend class Object_I<Cube>;

public:
  Cube(const vector_float3 &translations, const float rotation_magnitude,
       const vector_float3 &rotation_axis);
  ~Cube();
};