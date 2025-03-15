#pragma once

#include "object.h"

template <typename Derived> class Object_I : public Object {
private:
  Derived *m_derived = static_cast<Derived *>(this);

public:
  size_t get_vertex_count() const override {
    return m_derived->m_verticies.size();
  }

  size_t get_vertex_start() const override { return m_derived->m_vertex_start; }

  Vertex *get_vertex_c_array() const override {
    return m_derived->m_verticies.data();
  }

  Texture *get_texture() const override { return m_derived->m_texture; }

  MTL::PrimitiveType get_primitive_type() const override {
    return m_derived->m_prim_type;
  }

  Transformations get_transformations() const override {
    return m_derived->m_transformations;
  }

  void set_texture(Texture *texture) override {
    m_derived->m_texture = texture;
  }
};