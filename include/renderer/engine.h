#pragma once

#include "../objects/primitives/object.h"
#include "camera.h"
#include "texture.h"

#include <AppKit/AppKit.hpp>
#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>
#include <QuartzCore/QuartzCore.hpp>

#include <GLFW/glfw3.h>
#include <simd/simd.h>

#include <cstdint>
#include <memory>
#include <vector>

class Engine {
private:
  Camera *m_camera = nullptr;

  GLFWwindow *m_window = nullptr;
  NS::Window *m_ns_window = nullptr;
  float m_aspect_ratio;

  MTL::Device *m_device = nullptr;
  MTL::Library *m_default_library = nullptr;
  MTL::CommandQueue *m_command_queue = nullptr;
  MTL::CommandBuffer *m_command_buffer = nullptr;
  MTL::RenderPassDescriptor *m_render_pass_descriptor = nullptr;
  MTL::RenderPipelineState *m_render_pso = nullptr;
  MTL::DepthStencilState *m_depth_stencil_state = nullptr;

  MTL::TriangleFillMode m_triangle_fill_mode = MTL::TriangleFillModeFill;

  Texture *MSAA_texture = nullptr, *depth_texture = nullptr;
  const int m_sample_count;

  CA::MetalLayer *m_layer = nullptr;
  CA::MetalDrawable *m_drawable = nullptr;

  std::vector<MTL::Buffer *> m_vertex_buffers, m_clip_matrix_buffers;
  std::vector<std::shared_ptr<Object>> m_objects;

private:
  static void framebuffer_size_callback(GLFWwindow *window, const int width,
                                        const int height);
  void resize_framebuffer(const int width, const int height);

  void update_render_pass_descriptor();

  void create_depth_and_msaa_textures();

  void render_object(const auto &obj,
                     MTL::RenderCommandEncoder *render_command_encoder,
                     MTL::Buffer *vertex_buffer,
                     MTL::Buffer *clip_matrix_buffer);

public:
  Engine(const int width, const int height, Camera *camera,
         const int sample_count);
  ~Engine();

  MTL::Device *get_device();

  void add_object(Object *obj);

  void stage();
  void render();

  void set_triangle_fill_mode(MTL::TriangleFillMode triangle_fill_mode);
};