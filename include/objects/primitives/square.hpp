#pragma once

#include "../../renderer/texture.hpp"
#include "object_i.hpp"

#include <array>

class Square : public Object_I<Square> {
protected:
  std::array<Vertex, 6> m_vertices = {{
      {{-0.5f, -0.5f, 0.5f, 1.0f}, {0.0f, 0.0f}}, // Bottom-left
      {{-0.5f, 0.5f, 0.5f, 1.0f}, {0.0f, 1.0f}},  // Top-left
      {{0.5f, 0.5f, 0.5f, 1.0f}, {1.0f, 1.0f}},   // Top-right
      {{-0.5f, -0.5f, 0.5f, 1.0f}, {0.0f, 0.0f}}, // Bottom-left (again)
      {{0.5f, 0.5f, 0.5f, 1.0f}, {1.0f, 1.0f}},   // Top-right
      {{0.5f, -0.5f, 0.5f, 1.0f}, {1.0f, 0.0f}}   // Bottom-right
  }};

  Texture *m_texture;

  friend class Object_I<Square>;

public:
  Square();
  ~Square();
};