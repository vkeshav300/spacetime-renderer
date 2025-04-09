#pragma once

#include "../apple_math.h"
#include "../renderer/texture.hpp"
#include "shapes.hpp"

#include <Metal/Metal.hpp>
#include <simd/simd.h>

#include <memory>

class Object {
protected:
  std::shared_ptr<Texture> m_texture = nullptr;

  MTL::Buffer *m_vertex_buffer;
  vertex_vector m_vertices;

  MTL::Buffer *m_transformations_buffer;
  vector_float3 m_position = {0.0f, 0.0f, 0.0f};
  vector_float4 m_rotations = {0.0f, 0.0f, 0.0f, 0.0f};

public:
  Object(const vertex_vector &vertices);
  ~Object();

  Vertex *get_vertex_carray();
  NS::UInteger get_vertex_count() const;
  MTL::Buffer *get_vertex_buffer() const;
  void set_vertex_buffer(MTL::Buffer *vertex_buffer);

  void set_texture(Texture *texture);
  std::shared_ptr<Texture> get_texture() const;

  MTL::Buffer *get_transformations_buffer() const;
  void set_transformations_buffer(MTL::Buffer *transformations_buffer);
  vector_float3 get_position() const;
  vector_float4 get_rotations() const;
  void move(const float x, const float y, const float z);
  void rotate(const float x, const float y, const float z,
              const radians magnitude);
};
