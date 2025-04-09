#include "bridges/glfw.hpp"

NS::Window *get_ns_window(GLFWwindow *window, CA::MetalLayer *layer) {
  NSWindow *_window = glfwGetCocoaWindow(window);

  _window.contentView.layer = (__bridge CALayer *)layer;
  _window.contentView.wantsLayer = YES;

  return (__bridge NS::Window *)_window;
}
