#include "objects/object.hpp"

Object::Object(const vertex_vector &vertices) : m_vertices(vertices) {
    m_vertices.shrink_to_fit();
}

Object::~Object() {}

Vertex *Object::get_vertex_carray() {
    return m_vertices.data();
}

NS::UInteger Object::get_vertex_count() const {
    return m_vertices.size();
}
	
void Object::set_texture(std::shared_ptr<Texture> texture) {
    m_texture = texture;
}

std::shared_ptr<Texture> Object::get_texture() const {
    return m_texture;
}
	
vector_float3 Object::get_translations() const {
    return m_translations;
}
vector_float4 Object::get_rotations() const {
    return m_rotations;
}

void Object::translate(const float x, const float y, const float z) {
    m_translations = vector_float3{x, y, z};
}

void Object::rotate(const float x, const float y, const float z, const radians magnitude) {
    m_rotations = vector_float4{x, y, z, magnitude};
}