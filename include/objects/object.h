#pragma once

#include "../renderer/texture.h"
#include "data.h"

#include <Metal/Metal.hpp>
#include <simd/simd.h>

#include <vector>

class Object {
public:
  Texture *m_texture = nullptr;

  std::vector<Vertex> m_verticies;
  Transformations m_transformations;

  MTL::PrimitiveType m_prim_type = MTL::PrimitiveTypeTriangle;
  size_t m_start_vertex = 0;

public:
  Object() = default;

  virtual ~Object() = default;
};