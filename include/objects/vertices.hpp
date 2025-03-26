#pragma once

#include "../renderer/gpu_buffers.h"

#include <vector>

using vtx_vec = std::vector<Vertex>;

namespace vertices_set {
    const vtx_vec triangle = {
        {{{-0.5f, -0.5f, 0.0f, 1.0f}, {0.0f, 0.0f}},
         {{0.5f, -0.5f, 0.0f, 1.0f}, {0.0f, 0.0f}},
         {{0.0f, 0.5f, 0.0f, 1.0f}, {0.0f, 0.0f}}}};

    const vtx_vec square = {{
        {{-0.5f, -0.5f, 0.5f, 1.0f}, {0.0f, 0.0f}}, // Bottom-left
        {{-0.5f, 0.5f, 0.5f, 1.0f}, {0.0f, 1.0f}},  // Top-left
        {{0.5f, 0.5f, 0.5f, 1.0f}, {1.0f, 1.0f}},   // Top-right
        {{-0.5f, -0.5f, 0.5f, 1.0f}, {0.0f, 0.0f}}, // Bottom-left (again)
        {{0.5f, 0.5f, 0.5f, 1.0f}, {1.0f, 1.0f}},   // Top-right
        {{0.5f, -0.5f, 0.5f, 1.0f}, {1.0f, 0.0f}}   // Bottom-right
    }};
};