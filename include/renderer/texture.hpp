#pragma once

#include <Metal/Metal.hpp>

#include <stb_image.h>

class Texture {
private:
	MTL::Texture *m_texture;
	int m_width, m_height, m_channels;

public:
	Texture(MTL::Device *device, const char *path);
	~Texture();

	MTL::Texture *get_mtl_texture() const;
};