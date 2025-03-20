#pragma once

#include "object_i.hpp"
#include "../../renderer/gpu_buffers.h"

#include <array>

class Triangle: public Object_I<Triangle> {
private:
	std::array<Vertex, 3> m_verticies;
	
	Texture *m_texture;

	friend class Object_I<Triangle>;

public:
	Triangle();
	~Triangle();
};