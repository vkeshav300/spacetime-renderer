#pragma once

#include <Metal/Metal.hpp>
#include <Foundation/Foundation.hpp>
#include <QuartzCore/QuartzCore.hpp>
#include <AppKit/AppKit.hpp>

#include <GLFW/glfw3.h>

class Engine {
private:
    GLFWwindow *m_window;
    NS::Window *m_ns_window;

    MTL::Device *m_device;

    CA::MetalLayer *m_layer;
public:
    Engine(const int width, const int height);
    ~Engine();

    void stage();
    void render();
};