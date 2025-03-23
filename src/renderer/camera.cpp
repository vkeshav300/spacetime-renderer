#include "renderer/camera.hpp"

Camera::Camera(const vector_float3 &position, const vector_float3 &target,
               const radians fov, const float near_z, const float far_z)
    : m_position(position), m_target(target), m_fov(fov), m_near_z(near_z),
      m_far_z(far_z) {}

Camera::~Camera() {}

matrix_float4x4 Camera::get_camera_matrix4x4(const float aspect_ratio) {
  return matrix_multiply(
      apple_math::make_perspective_projection_matrix4x4(m_fov, aspect_ratio,
                                                        m_near_z, m_far_z),
      apple_math::make_look_at_matrix4x4(m_position, m_target));
}