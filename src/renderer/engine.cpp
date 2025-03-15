#include "renderer/engine.h"
#include "apple_math.h"
#include "bridges/glfw.h"
#include "objects/primitives/data.h"
#include "renderer/texture.h"

#include <simd/simd.h>

#include <cstdlib>
#include <stdexcept>

Engine::Engine(const int width, const int height, Camera *camera,
               const int sample_count)
    : m_camera(camera), m_device(MTL::CreateSystemDefaultDevice()),
      m_layer(CA::MetalLayer::layer()->retain()), m_sample_count(sample_count) {
  /* GLFW setup */
  glfwInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

  m_window = glfwCreateWindow(width, height, "Spacetime Renderer [Metal]",
                              nullptr, nullptr);

  int width_fb, height_fb;
  glfwGetFramebufferSize(m_window, &width_fb, &height_fb);

  glfwSetWindowUserPointer(m_window, this);
  glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

  m_aspect_ratio = width_fb / height_fb;

  /* Metal setup */
  m_layer->setDevice(m_device);
  m_layer->setPixelFormat(MTL::PixelFormatBGRA8Unorm);
  m_layer->setDrawableSize(CGSizeMake(width_fb, height_fb));
  m_ns_window = get_ns_window(m_window, m_layer)->retain();
}

Engine::~Engine() {
  /* Pointer cleanup */
  m_layer->release();
  m_ns_window->release();
  m_default_library->release();
  m_command_queue->release();

  /* GLFW cleanup */
  glfwDestroyWindow(m_window);
  glfwTerminate();
}

MTL::Device *Engine::get_device() { return m_device; }

void Engine::add_object(Object *obj) {
  const size_t obj_index = m_objects.size();

  m_objects.emplace_back(obj);
  m_vertex_buffers.emplace_back(m_device->newBuffer(
      obj->get_vertex_c_array(), obj->get_vertex_count() * sizeof(Vertex),
      MTL::ResourceStorageModeShared));
  m_clip_matrix_buffers.emplace_back(m_device->newBuffer(
      sizeof(matrix_float4x4), MTL::ResourceStorageModeShared));
}

void Engine::stage() {
  /* Load shaders */
  m_default_library = m_device->newDefaultLibrary();
  if (!m_default_library)
    throw std::runtime_error("Failed to load default library");

  m_command_queue = m_device->newCommandQueue()->retain();

  MTL::Function *vertex_function = m_default_library->newFunction(
      NS::String::string("vertex_shader", NS::ASCIIStringEncoding));
  if (!vertex_function)
    throw std::runtime_error("Failed to load vertex function");

  MTL::Function *fragment_function = m_default_library->newFunction(
      NS::String::string("fragment_shader", NS::ASCIIStringEncoding));
  if (!fragment_function)
    throw std::runtime_error("Failed to load fragment function");

  /* Render pipeline */
  MTL::RenderPipelineDescriptor *pipeline_descriptor =
      MTL::RenderPipelineDescriptor::alloc()->init();
  pipeline_descriptor->setLabel(
      NS::String::string("main_pipeline", NS::ASCIIStringEncoding));
  pipeline_descriptor->setVertexFunction(vertex_function);
  pipeline_descriptor->setFragmentFunction(fragment_function);
  assert(pipeline_descriptor);

  vertex_function->release();
  fragment_function->release();

  MTL::PixelFormat pixel_format = m_layer->pixelFormat();
  pipeline_descriptor->colorAttachments()->object(0)->setPixelFormat(
      pixel_format);

  pipeline_descriptor->setSampleCount(
      m_sample_count); // For multi-sampling anti-aliasing (MSAA)
  pipeline_descriptor->setDepthAttachmentPixelFormat(
      MTL::PixelFormatDepth32Float);

  NS::Error *err = nullptr;
  m_render_pso = m_device->newRenderPipelineState(pipeline_descriptor, &err);

  pipeline_descriptor->release();

  if (err) {
    err->release();
    throw std::runtime_error("Failed to create render pipeline state");
  }

  /* Depth calculations */
  MTL::DepthStencilDescriptor *depth_stencil_descriptor =
      MTL::DepthStencilDescriptor::alloc()->init();
  depth_stencil_descriptor->setDepthCompareFunction(
      MTL::CompareFunctionLessEqual);
  depth_stencil_descriptor->setDepthWriteEnabled(true);
  m_depth_stencil_state =
      m_device->newDepthStencilState(depth_stencil_descriptor);

  depth_stencil_descriptor->release();
}

void Engine::render_object(const auto &obj,
                           MTL::RenderCommandEncoder *render_command_encoder,
                           MTL::Buffer *vertex_buffer,
                           MTL::Buffer *clip_matrix_buffer) {
  /* Calculate rendering matricies */
  const Transformations obj_transformations = obj->get_transformations();
  const vector_float3 obj_translations = obj_transformations.translations;
  const matrix_float4x4 translation_matrix =
      apple_math::make_translation_matrix4x4(
          obj_translations.x, obj_translations.y, obj_translations.z);

  const vector_float3 obj_rotation_axis = obj_transformations.rotation_axis;
  const matrix_float4x4 rotation_matrix = apple_math::make_rotation_matrix4x4(
      glfwGetTime() / 2.0f * obj_transformations.rotation_magnitude,
      vector_float3{obj_rotation_axis.x, obj_rotation_axis.y,
                    obj_rotation_axis.z});

  const matrix_float4x4 model_matrix =
      matrix_multiply(translation_matrix, rotation_matrix);

  const matrix_float4x4 camera_matrix =
      m_camera->get_camera_matrix4x4(m_aspect_ratio);

  const matrix_float4x4 clip_matrix =
      matrix_multiply(camera_matrix, model_matrix);

  std::memcpy(clip_matrix_buffer->contents(), &clip_matrix,
              sizeof(matrix_float4x4));

  /* Render object */
  render_command_encoder->setVertexBuffer(vertex_buffer, 0, 0);
  render_command_encoder->setVertexBuffer(clip_matrix_buffer, 0, 1);

  Texture *texture = obj->get_texture();
  if (texture)
    render_command_encoder->setFragmentTexture(
        texture->get_mtl_texture(), 0);

  render_command_encoder->drawPrimitives(obj->get_primitive_type(),
                                         obj->get_vertex_start(),
                                         obj->get_vertex_count());
}

void Engine::render() {
  while (!glfwWindowShouldClose(m_window)) {
    NS::AutoreleasePool *pool =
        NS::AutoreleasePool::alloc()->init(); // Automatic memory management

    m_drawable =
        m_layer->nextDrawable(); // Next drawable (texture to render to)

    if (!m_drawable) {
      pool->release();
      continue;
    }

    m_command_buffer =
        m_command_queue
            ->commandBuffer(); // Create command buffer to hold commands for GPU

    m_render_pass_descriptor = MTL::RenderPassDescriptor::alloc()->init();

    if (!MSAA_texture | !depth_texture)
      create_depth_and_msaa_textures();

    update_render_pass_descriptor();

    /* Encodes render commands */
    MTL::RenderCommandEncoder *render_command_encoder =
        m_command_buffer->renderCommandEncoder(m_render_pass_descriptor);
    render_command_encoder->setFrontFacingWinding(MTL::WindingCounterClockwise);
    render_command_encoder->setCullMode(MTL::CullModeBack);
    render_command_encoder->setTriangleFillMode(m_triangle_fill_mode);
    render_command_encoder->setRenderPipelineState(m_render_pso);
    render_command_encoder->setDepthStencilState(m_depth_stencil_state);

    /* Render objects */
    for (size_t i = 0; i < m_objects.size(); i++)
      render_object(m_objects[i], render_command_encoder, m_vertex_buffers[i],
                    m_clip_matrix_buffers[i]);

    render_command_encoder->endEncoding();

    /* Send rendered frame to GPU */
    m_command_buffer->presentDrawable(m_drawable);
    m_command_buffer->commit();

    // Disabled due to being a performance-killer (makes CPU wait for GPU
    // completion) m_command_buffer->waitUntilCompleted();

    pool->release(); // Cleanup memory

    glfwPollEvents();
  }
}

void Engine::set_triangle_fill_mode(MTL::TriangleFillMode triangle_fill_mode) {
  m_triangle_fill_mode = triangle_fill_mode;
}

void Engine::framebuffer_size_callback(GLFWwindow *window, const int width,
                                       const int height) {
  Engine *engine = reinterpret_cast<Engine *>(glfwGetWindowUserPointer(window));
  engine->resize_framebuffer(width, height);
}

void Engine::resize_framebuffer(const int width, const int height) {
  m_layer->setDrawableSize(CGSizeMake(width, height));
  m_aspect_ratio = static_cast<float>(width) / height;

  create_depth_and_msaa_textures();
  m_drawable = m_layer->nextDrawable();
  update_render_pass_descriptor();
}

void Engine::update_render_pass_descriptor() {
  m_render_pass_descriptor->colorAttachments()->object(0)->setTexture(
      MSAA_texture->get_mtl_texture());
  m_render_pass_descriptor->colorAttachments()->object(0)->setResolveTexture(
      m_drawable->texture());
  m_render_pass_descriptor->depthAttachment()->setTexture(
      depth_texture->get_mtl_texture());
}

void Engine::create_depth_and_msaa_textures() {
  delete MSAA_texture;
  delete depth_texture;

  MSAA_texture = new Texture(
      m_device, MTL::TextureType2DMultisample, MTL::PixelFormatBGRA8Unorm,
      m_layer->drawableSize().width, m_layer->drawableSize().height,
      m_sample_count, MTL::TextureUsageRenderTarget);

  depth_texture = new Texture(
      m_device, MTL::TextureType2DMultisample, MTL::PixelFormatDepth32Float,
      m_layer->drawableSize().width, m_layer->drawableSize().height,
      m_sample_count, MTL::TextureUsageRenderTarget);
}