#pragma once

#include <simd/simd.h>

struct Vertex {
  vector_float4 position;
  vector_float2 texture_coordinate;
};

struct Transformations {
  vector_float3 translations;
  vector_float3 rotation_axis;
  float rotation_magnitude;
};