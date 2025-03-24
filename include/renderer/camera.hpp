#pragma once

#include "apple_math.h"

#include <simd/simd.h>

class Camera {
private:
  vector_float3 m_position, m_target;
  radians m_fov;
  float m_near_z, m_far_z;

public:
  Camera(const vector_float3 &position, const vector_float3 &target,
         const radians fov, const float near_z, const float far_z);
  ~Camera();

  matrix_float4x4 get_camera_matrix4x4(const float aspect_ratio);
};