#pragma once

#include <simd/simd.h>

struct Vertex {
  vector_float4 position;
  vector_float2 texture_coordinate;
};

struct Transformations {
  matrix_float4x4 clip_matrix;
};