#include "objects/cube.h"

Cube::Cube(const vector_float3 &translations, const float rotation_magnitude,
           const vector_float3 &rotation_axis) {
  m_transformations.translations = translations;
  m_transformations.rotation_magnitude = rotation_magnitude;
  m_transformations.rotation_axis = rotation_axis;
  m_verticies = {
      // Front face
      {{-1.0f, -1.0f, 1.0f}, {0.0f, 0.0f}}, // Bottom-left
      {{1.0f, -1.0f, 1.0f}, {1.0f, 0.0f}},  // Bottom-right
      {{1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},   // Top-right
      {{1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},   // Top-right
      {{-1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},  // Top-left
      {{-1.0f, -1.0f, 1.0f}, {0.0f, 0.0f}}, // Bottom-left

      // Back face
      {{1.0f, -1.0f, -1.0f}, {0.0f, 0.0f}},  // Bottom-right
      {{-1.0f, -1.0f, -1.0f}, {1.0f, 0.0f}}, // Bottom-left
      {{-1.0f, 1.0f, -1.0f}, {1.0f, 1.0f}},  // Top-left
      {{-1.0f, 1.0f, -1.0f}, {1.0f, 1.0f}},  // Top-left
      {{1.0f, 1.0f, -1.0f}, {0.0f, 1.0f}},   // Top-right
      {{1.0f, -1.0f, -1.0f}, {0.0f, 0.0f}},  // Bottom-right

      // Left face
      {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f}}, // Bottom-left
      {{-1.0f, -1.0f, 1.0f}, {1.0f, 0.0f}},  // Bottom-right
      {{-1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},   // Top-right
      {{-1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},   // Top-right
      {{-1.0f, 1.0f, -1.0f}, {0.0f, 1.0f}},  // Top-left
      {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f}}, // Bottom-left

      // Right face
      {{1.0f, -1.0f, 1.0f}, {0.0f, 0.0f}},  // Bottom-left
      {{1.0f, -1.0f, -1.0f}, {1.0f, 0.0f}}, // Bottom-right
      {{1.0f, 1.0f, -1.0f}, {1.0f, 1.0f}},  // Top-right
      {{1.0f, 1.0f, -1.0f}, {1.0f, 1.0f}},  // Top-right
      {{1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},   // Top-left
      {{1.0f, -1.0f, 1.0f}, {0.0f, 0.0f}},  // Bottom-left

      // Top face
      {{-1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},  // Bottom-left
      {{1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},   // Bottom-right
      {{1.0f, 1.0f, -1.0f}, {1.0f, 1.0f}},  // Top-right
      {{1.0f, 1.0f, -1.0f}, {1.0f, 1.0f}},  // Top-right
      {{-1.0f, 1.0f, -1.0f}, {0.0f, 1.0f}}, // Top-left
      {{-1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},  // Bottom-left

      // Bottom face
      {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f}}, // Bottom-left
      {{1.0f, -1.0f, -1.0f}, {1.0f, 0.0f}},  // Bottom-right
      {{1.0f, -1.0f, 1.0f}, {1.0f, 1.0f}},   // Top-right
      {{1.0f, -1.0f, 1.0f}, {1.0f, 1.0f}},   // Top-right
      {{-1.0f, -1.0f, 1.0f}, {0.0f, 1.0f}},  // Top-left
      {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f}}, // Bottom-left
  };
}
Cube::~Cube() {}