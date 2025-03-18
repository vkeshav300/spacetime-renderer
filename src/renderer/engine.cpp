#include "renderer/engine.hpp"
#include "bridges/glfw.hpp"

#include <stdexcept>

Engine::Engine(const int width, const int height) : m_device(MTL::CreateSystemDefaultDevice()), m_layer(CA::MetalLayer::layer()) {
    /* Window */
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    m_window = glfwCreateWindow(width, height, "Spacetime Renderer [Metal]", nullptr, nullptr);

    if (!m_window) {
        glfwTerminate();
        m_device->release();

        throw std::runtime_error("Failed to create window");
    }

    m_layer->setDevice(m_device);
    m_layer->setPixelFormat(MTL::PixelFormatBGRA8Unorm);

    m_ns_window = get_ns_window(m_window, m_layer);
}

Engine::~Engine() {
    glfwTerminate();

    m_device->release();
}

void Engine::stage() {}

void Engine::render() {
    while (!glfwWindowShouldClose(m_window)) {
        glfwPollEvents();
    }
}