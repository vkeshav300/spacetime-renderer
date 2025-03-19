#pragma once

#include "object.hpp"
#include "../../renderer/gpu_buffers.h"

#include <Metal/Metal.hpp>

template <typename Derived>
class Object_I: public Object {
protected:
	Derived *m_derived = static_cast<Derived *>(this);

public:
	Vertex *get_vertex_carray() const override {
		return m_derived->m_verticies.data();
	}

	NS::UInteger get_vertex_count() const override {
		return static_cast<NS::UInteger>(m_derived->m_verticies.size());
	}
};
