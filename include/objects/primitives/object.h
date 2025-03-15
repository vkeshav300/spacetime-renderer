#pragma once

#include "../../renderer/texture.h"
#include "data.h"

#include <Metal/Metal.hpp>

class Object {
public:
  virtual ~Object() = default;
  virtual size_t get_vertex_count() const = 0;
  virtual size_t get_vertex_start() const = 0;
  virtual Vertex *get_vertex_c_array() const = 0;
  virtual Texture *get_texture() const = 0;
  virtual MTL::PrimitiveType get_primitive_type() const = 0;
  virtual Transformations get_transformations() const = 0;
  virtual void set_texture(Texture *texture) = 0;
};