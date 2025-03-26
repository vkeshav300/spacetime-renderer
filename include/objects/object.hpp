#pragma once

#include "../apple_math.h"
#include "../renderer/texture.hpp"
#include "shapes.hpp"

#include <Metal/Metal.hpp>
#include <simd/simd.h>

#include <memory>

class Object {
protected:
  vector_float3 m_translations = {0.0f, 0.0f, 0.0f};
  vector_float4 m_rotations = {0.0f, 0.0f, 0.0f, 0.0f};

  vertex_vector m_vertices;

  std::shared_ptr<Texture> m_texture = nullptr;

public:
  Object(const vertex_vector &vertices);
  ~Object();

  Vertex *get_vertex_carray();
  NS::UInteger get_vertex_count() const;

  void set_texture(std::shared_ptr<Texture> texture);
  std::shared_ptr<Texture> get_texture() const;

  vector_float3 get_translations() const;
  vector_float4 get_rotations() const;
  void translate(const float x, const float y, const float z);
  void rotate(const float x, const float y, const float z,
              const radians magnitude);
};