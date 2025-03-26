#pragma once

#include "../renderer/gpu_buffers.h"

#include <vector>

using vertex_vector = std::vector<Vertex>;

namespace shapes {
const vertex_vector triangle = {{{{-0.5f, -0.5f, 0.0f, 1.0f}, {0.0f, 0.0f}},
                                 {{0.5f, -0.5f, 0.0f, 1.0f}, {0.0f, 0.0f}},
                                 {{0.0f, 0.5f, 0.0f, 1.0f}, {0.0f, 0.0f}}}};

const vertex_vector square = {{
    {{-0.5f, -0.5f, 0.5f, 1.0f}, {0.0f, 0.0f}}, // Bottom-left
    {{-0.5f, 0.5f, 0.5f, 1.0f}, {0.0f, 1.0f}},  // Top-left
    {{0.5f, 0.5f, 0.5f, 1.0f}, {1.0f, 1.0f}},   // Top-right
    {{-0.5f, -0.5f, 0.5f, 1.0f}, {0.0f, 0.0f}}, // Bottom-left (again)
    {{0.5f, 0.5f, 0.5f, 1.0f}, {1.0f, 1.0f}},   // Top-right
    {{0.5f, -0.5f, 0.5f, 1.0f}, {1.0f, 0.0f}}   // Bottom-right
}};
}; // namespace shapes