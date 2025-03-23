#pragma once

#include "object_i.hpp"
#include "../../renderer/texture.hpp"

#include <array>

class Square: public Object_I<Square> {
private:
	std::array<Vertex, 6> m_verticies;
	
	Texture *m_texture;

	friend class Object_I<Square>;
public:
	Square();
	~Square();
};