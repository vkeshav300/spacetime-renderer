#include "objects/object.hpp"

Object::Object(const vertex_vector &vertices) : m_vertices(vertices) {
  m_vertices.shrink_to_fit();
}

Object::~Object() {
  m_vertex_buffer->release();
  m_transformations_buffer->release();
  m_appearance_buffer->release();
}

Vertex *Object::get_vertex_carray() { return m_vertices.data(); }

NS::UInteger Object::get_vertex_count() const { return m_vertices.size(); }

MTL::Buffer *Object::get_vertex_buffer() const { return m_vertex_buffer; }

void Object::set_vertex_buffer(MTL::Buffer *vertex_buffer) {
  m_vertex_buffer = vertex_buffer;
}

void Object::set_texture(Texture *texture) {
  m_texture = std::shared_ptr<Texture>(texture);
}

void Object::set_color(const Color &color) {
  m_texture.reset();
  m_texture = nullptr;
  m_color = color;
}

void Object::set_appearance_buffer(MTL::Buffer *appearance_buffer) {
  m_appearance_buffer = appearance_buffer;
}

std::shared_ptr<Texture> Object::get_texture() const { return m_texture; }

Color Object::get_color() const { return m_color; }

MTL::Buffer *Object::get_appearance_buffer() const {
  return m_appearance_buffer;
}

MTL::Buffer *Object::get_transformations_buffer() const {
  return m_transformations_buffer;
}

void Object::set_transformations_buffer(MTL::Buffer *transformations_buffer) {
  m_transformations_buffer = transformations_buffer;
}

vector_float3 Object::get_position() const { return m_position; }

vector_float4 Object::get_rotations() const { return m_rotations; }

void Object::move(const float x, const float y, const float z) {
  m_position = vector_float3{x, y, z};
}

void Object::rotate(const float x, const float y, const float z,
                    const radians magnitude) {
  m_rotations = vector_float4{x, y, z, magnitude};
}
