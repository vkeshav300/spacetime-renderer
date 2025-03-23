#pragma once

#include "../../renderer/gpu_buffers.h"
#include "../../renderer/texture.hpp"
#include "object.hpp"

#include <Metal/Metal.hpp>
#include <simd/simd.h>

template <typename Derived> class Object_I : public Object {
protected:
  Derived *m_derived = static_cast<Derived *>(this);

public:
  Vertex *get_vertex_carray() const override {
    return m_derived->m_vertices.data();
  }

  NS::UInteger get_vertex_count() const override {
    return static_cast<NS::UInteger>(m_derived->m_vertices.size());
  }

  void set_texture(Texture *texture) override {
    m_derived->m_texture = texture;
  }

  Texture *get_texture() const override { return m_derived->m_texture; }

  vector_float3 get_translations() const override {
    return m_derived->m_translations;
  }

  void translate(const float x, const float y, const float z) override {
    m_derived->m_translations = vector_float3{x, y, z};
  }

  vector_float4 get_rotations() const override {
    return m_derived->m_rotations;
  }

  void rotate(const float x, const float y, const float z,
              const float magnitude) override {
    m_derived->m_rotations = vector_float4{x, y, z, magnitude};
  }
};
