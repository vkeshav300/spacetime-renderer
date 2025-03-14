#pragma once

#include <Metal/Metal.hpp>

#include <cstdint>

class Texture {
private:
  MTL::Device *m_device = nullptr;

  MTL::Texture *m_texture = nullptr;
  int m_width, m_height, m_channels;

public:
  Texture(MTL::Device *device, const char *path);
  Texture(MTL::Device *device, const MTL::TextureType mtl_texture_type,
          const MTL::PixelFormat mtl_pixel_format, const double width,
          const double height, const uint16_t sample_count,
          MTL::TextureUsage mtl_usage);
  ~Texture();

  MTL::Texture *get_mtl_texture();
};