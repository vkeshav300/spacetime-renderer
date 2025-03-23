#pragma once

#include "../../renderer/texture.hpp"
#include "object_i.hpp"

#include <array>

class Square : public Object_I<Square> {
private:
  std::array<Vertex, 6> m_verticies;

  Texture *m_texture;

  vector_float3 m_translations;
  vector_float4 m_rotations;

  friend class Object_I<Square>;

public:
  Square();
  ~Square();
};