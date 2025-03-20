#pragma once

#include "../objects/primitives/object.hpp"
#include "gpu_buffers.h"

#include <Metal/Metal.hpp>
#include <Foundation/Foundation.hpp>
#include <QuartzCore/QuartzCore.hpp>
#include <AppKit/AppKit.hpp>

#include <GLFW/glfw3.h>

#include <vector>
#include <memory>

class Engine {
private:
    GLFWwindow *m_window;
    NS::Window *m_ns_window;

    MTL::Device *m_device;
    MTL::Library *m_default_library;
    MTL::CommandQueue *m_command_queue;
    MTL::CommandBuffer *m_command_buffer;
    MTL::RenderPipelineState *m_render_pso;

    CA::MetalLayer *m_layer;
    CA::MetalDrawable *m_drawable;

    std::vector<std::shared_ptr<Object>> m_objects;
    std::vector<MTL::Buffer *> m_vertex_buffers;

private:
    void create_render_pipeline();

    void render_object(const std::shared_ptr<Object> &obj, MTL::RenderCommandEncoder *render_command_encoder, const MTL::Buffer *vertex_buffer);

    static void framebuffer_size_callback(GLFWwindow *window, const int width, const int height);
    void resize_framebuffer(const int width, const int height);

public:
    Engine(const int width, const int height);
    ~Engine();

    void add_object(Object *obj);

    void stage();
    void render();
};