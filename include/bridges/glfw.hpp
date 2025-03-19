#pragma once

#include <AppKit/AppKit.hpp>
#include <QuartzCore/QuartzCore.hpp>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#define GLFW_EXPOSE_NATIVE_COCOA
#include <GLFW/glfw3native.h>

NS::Window *get_ns_window(GLFWwindow *window, CA::MetalLayer *layer);