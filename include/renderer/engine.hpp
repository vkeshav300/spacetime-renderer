#pragma once

#include "../objects/object.hpp"
#include "camera.hpp"
#include "gpu_buffers.h"
#include "texture.hpp"

#include <AppKit/AppKit.hpp>
#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>
#include <QuartzCore/QuartzCore.hpp>
#include <simd/simd.h>

#include <GLFW/glfw3.h>

#include <memory>
#include <vector>

class Engine {
private:
  std::shared_ptr<Camera> m_camera;

  GLFWwindow *m_window;
  NS::Window *m_ns_window;
  float m_aspect_ratio;

  MTL::Device *m_device;
  MTL::Library *m_default_library;
  MTL::CommandQueue *m_command_queue;
  MTL::CommandBuffer *m_command_buffer;
  MTL::RenderPipelineState *m_render_pso;

  CA::MetalLayer *m_layer;
  CA::MetalDrawable *m_drawable;

  std::vector<std::shared_ptr<Object>> m_objects;
  std::vector<MTL::Buffer *> m_vertex_buffers;
  std::vector<MTL::Buffer *> m_clip_matrix_buffers;

private:
  void create_render_pipeline();

  void render_object(const std::shared_ptr<Object> &obj,
                     MTL::RenderCommandEncoder *render_command_encoder,
                     const MTL::Buffer *vertex_buffer,
                     MTL::Buffer *clip_matrix_buffer,
                     const matrix_float4x4 &camera_matrix);

  static void framebuffer_size_callback(GLFWwindow *window, const int width,
                                        const int height);
  void resize_framebuffer(const int width, const int height);

public:
  Engine(std::shared_ptr<Camera> camera, const int width, const int height);
  ~Engine();

  MTL::Device *get_device();

  void add_object(Object *obj);

  void stage();
  void render();
};