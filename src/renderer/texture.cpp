#include "renderer/texture.hpp"

#include <stdexcept>

Texture::Texture(MTL::Device *device, const char *path) {
  /* Format image for metal */
  stbi_set_flip_vertically_on_load(true);

  unsigned char *img =
      stbi_load(path, &m_width, &m_height, &m_channels, STBI_rgb_alpha);
  if (!img)
    throw std::runtime_error("Failed to load texture");

  MTL::TextureDescriptor *texture_descriptor =
      MTL::TextureDescriptor::alloc()->init();
  texture_descriptor->setPixelFormat(MTL::PixelFormatRGBA8Unorm);
  texture_descriptor->setWidth(m_width);
  texture_descriptor->setHeight(m_height);

  m_texture = device->newTexture(texture_descriptor);
  texture_descriptor->release();

  MTL::Region region = MTL::Region::Make2D(0, 0, m_width, m_height);
  m_texture->replaceRegion(region, 0, img, m_width * 4);

  stbi_image_free(img);
}

Texture::Texture(MTL::Device *device, const MTL::TextureType &texture_type,
                 const MTL::PixelFormat &pixel_format, const double width,
                 const double height, const MTL::TextureUsage &usage,
                 const size_t sample_count) {
  MTL::TextureDescriptor *texture_descriptor =
      MTL::TextureDescriptor::alloc()->init();
  texture_descriptor->setTextureType(texture_type);
  texture_descriptor->setPixelFormat(pixel_format);
  texture_descriptor->setWidth(width);
  texture_descriptor->setHeight(height);
  texture_descriptor->setUsage(usage);
  texture_descriptor->setSampleCount(sample_count);

  m_texture = device->newTexture(texture_descriptor);
  texture_descriptor->release();
}

Texture::~Texture() { m_texture->release(); }

MTL::Texture *Texture::get_mtl_texture() const { return m_texture; }
