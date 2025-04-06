#pragma once

#include <Metal/Metal.hpp>
#include <Foundation/Foundation.hpp> 

#include <stb_image.h>

class Texture {
private:
  MTL::Texture *m_texture;
  int m_width, m_height, m_channels;

public:
  Texture(MTL::Device *device, const char *path);
  Texture(MTL::Device *device, const MTL::TextureType &texture_type, const MTL::PixelFormat &pixel_format, const double width, const double height, const MTL::TextureUsage &usage, const size_t sample_count);
  ~Texture();

  MTL::Texture *get_mtl_texture() const;
};
