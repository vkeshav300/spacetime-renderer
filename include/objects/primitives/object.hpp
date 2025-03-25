#pragma once

#include "../../apple_math.h"
#include "../../renderer/gpu_buffers.h"
#include "../../renderer/texture.hpp"

#include <Metal/Metal.hpp>
#include <simd/simd.h>

#include <memory>

class Object {
protected:
  vector_float3 m_translations = {0.0f, 0.0f, 0.0f};
  vector_float4 m_rotations = {0.0f, 0.0f, 0.0f, 0.0f};

public:
  virtual ~Object() = default;

  virtual Vertex *get_vertex_carray() const = 0;
  virtual NS::UInteger get_vertex_count() const = 0;

  virtual void set_texture(std::shared_ptr<Texture> texture) = 0;
  virtual std::shared_ptr<Texture> get_texture() const = 0;

  virtual vector_float3 get_translations() const = 0;
  virtual void translate(const float x, const float y, const float z) = 0;
  virtual vector_float4 get_rotations() const = 0;
  virtual void rotate(const float x, const float y, const float z,
                      const float radians) = 0;
};
