#pragma once

#include "../../renderer/gpu_buffers.h"

#include <Metal/Metal.hpp>

class Object {
protected:

public:
	virtual ~Object() = default;

	virtual Vertex *get_vertex_carray() const = 0;
	virtual NS::UInteger get_vertex_count() const = 0;
};
