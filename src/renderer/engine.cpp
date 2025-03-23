#include "renderer/engine.hpp"
#include "bridges/glfw.hpp"

#include <cstring>
#include <stdexcept>

Engine::Engine(std::shared_ptr<Camera> camera, const int width,
               const int height)
    : m_device(MTL::CreateSystemDefaultDevice()),
      m_layer(CA::MetalLayer::layer()), m_camera(camera) {
  glfwInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  m_window = glfwCreateWindow(width, height, "Spacetime Renderer [Metal]",
                              nullptr, nullptr);

  if (!m_window) {
    glfwTerminate();
    m_device->release();

    throw std::runtime_error("Failed to create window");
  }

  glfwSetWindowUserPointer(m_window, this);
  glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

  int fb_width, fb_height;
  glfwGetFramebufferSize(m_window, &fb_width, &fb_height);
  m_aspect_ratio = static_cast<float>(fb_width) / fb_height;

  m_layer->setDevice(m_device);
  m_layer->setPixelFormat(MTL::PixelFormatBGRA8Unorm);
  m_layer->setDrawableSize(
      CGSizeMake(fb_width, fb_height)); // Fixes "fuzzy" borders of shapes

  m_ns_window = get_ns_window(m_window, m_layer);
}

Engine::~Engine() {
  glfwTerminate();

  for (auto &buffer : m_vertex_buffers)
    buffer->release();

  for (auto &buffer : m_clip_matrix_buffers)
    buffer->release();

  m_render_pso->release();
  m_command_queue->release();
  m_default_library->release();
  m_device->release();
}

MTL::Device *Engine::get_device() { return m_device; }

void Engine::add_object(Object *obj) {
  const size_t obj_index = m_objects.size();
  m_vertex_buffers.push_back(m_device->newBuffer(
      obj->get_vertex_carray(), obj->get_vertex_count() * sizeof(Vertex),
      MTL::ResourceStorageModeShared));
  m_clip_matrix_buffers.push_back(m_device->newBuffer(
      sizeof(matrix_float4x4), MTL::ResourceStorageModeShared));
  m_objects.push_back(std::shared_ptr<Object>(obj));
}

void Engine::create_render_pipeline() {
  /* Create render pipeline descriptor */
  MTL::RenderPipelineDescriptor *render_pipeline_descriptor =
      MTL::RenderPipelineDescriptor::alloc()->init();
  render_pipeline_descriptor->setLabel(NS::String::string(
      "Spacetime Renderer Rendering Pipeline", NS::ASCIIStringEncoding));
  render_pipeline_descriptor->colorAttachments()->object(0)->setPixelFormat(
      m_layer->pixelFormat());

  /* Set vertex shader */
  MTL::Function *vertex_shader = m_default_library->newFunction(
      NS::String::string("vertex_shader", NS::ASCIIStringEncoding));
  if (!vertex_shader)
    throw std::runtime_error("Failed to load vertex shader");

  render_pipeline_descriptor->setVertexFunction(vertex_shader);
  vertex_shader->release();

  /* Set fragment shader */
  MTL::Function *fragment_shader = m_default_library->newFunction(
      NS::String::string("fragment_shader", NS::ASCIIStringEncoding));
  if (!fragment_shader)
    throw std::runtime_error("Failed to load fragment shader");

  render_pipeline_descriptor->setFragmentFunction(fragment_shader);
  fragment_shader->release();

  /* Create render pipeline state from descriptor */
  NS::Error *render_pso_error = nullptr;
  m_render_pso = m_device->newRenderPipelineState(render_pipeline_descriptor,
                                                  &render_pso_error);
  if (render_pso_error)
    throw std::runtime_error("Failed to create render pipeline state");

  render_pipeline_descriptor->release();
}

void Engine::stage() {
  /* Loads library containing all GPU-running functions (from .metal files) */
  m_default_library = m_device->newDefaultLibrary();
  if (!m_default_library)
    throw std::runtime_error("Failed to load default library");

  /* Creates queue for holding GPU commands */
  m_command_queue = m_device->newCommandQueue();

  create_render_pipeline();
}

void Engine::render_object(const std::shared_ptr<Object> &obj,
                           MTL::RenderCommandEncoder *render_command_encoder,
                           const MTL::Buffer *vertex_buffer,
                           MTL::Buffer *clip_matrix_buffer,
                           const matrix_float4x4 &camera_matrix) {
  /* Calculate clip matrix from transformations */
  const matrix_float4x4 clip_matrix = matrix_multiply(
      matrix_multiply(camera_matrix, apple_math::make_translation_matrix4x4(
                                         obj->get_translations())),
      apple_math::make_rotation_matrix4x4(obj->get_rotations()));

  const Transformations transformations = {clip_matrix};
  std::memcpy(clip_matrix_buffer->contents(), &transformations,
              sizeof(matrix_float4x4));

  /* Set buffers for vertex shader */
  render_command_encoder->setVertexBuffer(vertex_buffer, 0, 0);
  render_command_encoder->setVertexBuffer(clip_matrix_buffer, 0, 1);

  std::shared_ptr<Texture> texture = obj->get_texture();
  if (texture)
    render_command_encoder->setFragmentTexture(texture->get_mtl_texture(), 0);

  render_command_encoder->drawPrimitives(MTL::PrimitiveTypeTriangle,
                                         static_cast<NS::UInteger>(0),
                                         obj->get_vertex_count());
}

void Engine::render() {
  while (!glfwWindowShouldClose(m_window)) {
    NS::AutoreleasePool *pool =
        NS::AutoreleasePool::alloc()
            ->init(); // Semi-automatic memory management

    /* Get next drawable frame */
    m_drawable = m_layer->nextDrawable();
    if (!m_drawable) {
      pool->release();
      continue;
    }

    m_command_buffer = m_command_queue->commandBuffer();

    /* Create render command */
    MTL::RenderPassDescriptor *render_pass_descriptor =
        MTL::RenderPassDescriptor::alloc()->init();
    MTL::RenderPassColorAttachmentDescriptor *color_descriptor =
        render_pass_descriptor->colorAttachments()->object(0);
    color_descriptor->setTexture(m_drawable->texture());
    color_descriptor->setLoadAction(MTL::LoadActionClear);
    color_descriptor->setClearColor(
        MTL::ClearColor(41.0f / 255.0f, 42.0f / 255.0f, 48.0f / 255.0f, 1.0));
    color_descriptor->setStoreAction(MTL::StoreActionStore);

    MTL::RenderCommandEncoder *render_command_encoder =
        m_command_buffer->renderCommandEncoder(render_pass_descriptor);
    render_command_encoder->setRenderPipelineState(m_render_pso);

    render_pass_descriptor->release();

    /* Render objects */
    const matrix_float4x4 camera_matrix = m_camera->get_camera_matrix4x4(
        m_aspect_ratio); // Camera matrix is defined here to only calculate 1
                         // camera matrix per render pass
    for (size_t i = 0; i < m_objects.size(); i++)
      render_object(m_objects[i], render_command_encoder, m_vertex_buffers[i],
                    m_clip_matrix_buffers[i], camera_matrix);

    /* Tell GPU frame is renderable */
    m_command_buffer->presentDrawable(m_drawable);
    render_command_encoder->endEncoding();
    m_command_buffer->commit();

#ifdef DEBUG
    m_command_buffer
        ->waitUntilCompleted(); // Forces CPU to wait for GPU completion
#endif

    pool->release();

    glfwPollEvents();
  }
}

void Engine::framebuffer_size_callback(GLFWwindow *window, const int width,
                                       const int height) {
  reinterpret_cast<Engine *>(glfwGetWindowUserPointer(window))
      ->resize_framebuffer(width, height);
}

void Engine::resize_framebuffer(const int width, const int height) {
  m_layer->setDrawableSize(CGSizeMake(width, height));
  m_aspect_ratio = static_cast<float>(width) / height;
}