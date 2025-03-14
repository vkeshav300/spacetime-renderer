#include "renderer/texture.h"

#include <stb_image.h>

#include <stdexcept>

Texture::Texture(MTL::Device *device, const char *path) : m_device(device) {
  /* Load image from path */
  stbi_set_flip_vertically_on_load(
      true); // Metal expects 0 coordinate on y-axis to be bottom of image, not
             // top

  unsigned char *image =
      stbi_load(path, &m_width, &m_height, &m_channels, STBI_rgb_alpha);
  if (image == NULL)
    throw std::runtime_error("Failed to load texture");

  /* Create texture in metal */
  MTL::TextureDescriptor *texture_descriptor =
      MTL::TextureDescriptor::alloc()->init();
  texture_descriptor->setPixelFormat(MTL::PixelFormatRGBA8Unorm);
  texture_descriptor->setWidth(m_width);
  texture_descriptor->setHeight(m_height);

  m_texture = device->newTexture(texture_descriptor);

  /* Load texture to texture buffer */
  MTL::Region region = MTL::Region(0, 0, 0, m_width, m_height, 1);
  NS::UInteger bytes_per_row = 4 * m_width;

  m_texture->replaceRegion(region, 0, image, bytes_per_row);

  /* Cleanup */
  texture_descriptor->release();
  stbi_image_free(image);
}

Texture::Texture(MTL::Device *device, const MTL::TextureType mtl_texture_type,
                 const MTL::PixelFormat mtl_pixel_format, const double width,
                 const double height, const uint16_t sample_count,
                 MTL::TextureUsage mtl_usage)
    : m_device(device) {
  MTL::TextureDescriptor *texture_descriptor =
      MTL::TextureDescriptor::alloc()->init();
  texture_descriptor->setTextureType(mtl_texture_type);
  texture_descriptor->setPixelFormat(mtl_pixel_format);
  texture_descriptor->setWidth(width);
  texture_descriptor->setHeight(height);
  texture_descriptor->setSampleCount(sample_count);
  texture_descriptor->setUsage(mtl_usage);

  m_texture = device->newTexture(texture_descriptor);
  texture_descriptor->release();
}

Texture::~Texture() {
  m_texture->release();
  m_texture = nullptr;
}

MTL::Texture *Texture::get_mtl_texture() { return m_texture; }