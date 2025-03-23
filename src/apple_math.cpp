#include "apple_math.h"

#include <cmath>

namespace apple_math {
matrix_float4x4 APPLE_SIMD_OVERLOAD make_matrix4x4(
    const float m00, const float m01, const float m02, const float m03,
    const float m10, const float m11, const float m12, const float m13,
    const float m20, const float m21, const float m22, const float m23,
    const float m30, const float m31, const float m32, const float m33) {
  return matrix_float4x4{
      vector_float4{m00, m01, m02, m03}, vector_float4{m10, m11, m12, m13},
      vector_float4{m20, m21, m22, m23}, vector_float4{m30, m31, m32, m33}};
}

matrix_float4x4 APPLE_SIMD_OVERLOAD make_translation_matrix4x4(const float x,
                                                               const float y,
                                                               const float z) {
  return make_matrix4x4(1, 0, 0, x, 0, 1, 0, y, 0, 0, 1, z, 0, 0, 0, 1);
}

matrix_float4x4 APPLE_SIMD_OVERLOAD
make_translation_matrix4x4(const vector_float3 &translations) {
  return make_translation_matrix4x4(translations.x, translations.y,
                                    translations.z);
}

matrix_float4x4 APPLE_SIMD_OVERLOAD
make_rotation_matrix4x4(const radians theta, vector_float3 axis) {
  if ((simd_length(axis) == 0) | (theta == 0))
    return make_matrix4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);

  axis = simd_normalize(axis);

  const float x = axis.x, y = axis.y, z = axis.z, ct = std::cosf(theta),
              st = std::sinf(theta), ci = 1 - ct;

  return make_matrix4x4(
      ct + x * x * ci, x * y * ci - z * st, x * z * ci + z * st, 0,
      x * y * ci + z * st, ct + y * y * ci, y * z * ci - x * st, 0,
      x * z * ci - y * st, y * z * ci + x * st, ct + z * z * ci, 0, 0, 0, 0, 1);
}

matrix_float4x4 APPLE_SIMD_OVERLOAD
make_rotation_matrix4x4(const vector_float4 &rotations) {
  return make_rotation_matrix4x4(
      rotations.w, vector_float3{rotations.x, rotations.y, rotations.z});
}

matrix_float4x4 APPLE_SIMD_OVERLOAD make_look_at_matrix4x4(
    const vector_float3 &position, const vector_float3 &target) {
  const vector_float3 f = simd_normalize(target - position),
                      r = simd_normalize(simd_cross(vector_float3{0, 1, 0}, f)),
                      u = simd_cross(f, r), nposition = -position;

  return make_matrix4x4(r.x, u.x, -f.x, simd_dot(nposition, r), r.y, u.y, -f.y,
                        simd_dot(nposition, u), r.z, u.z, -f.z,
                        simd_dot(nposition, f), 0, 0, 0, 1);
}

matrix_float4x4 APPLE_SIMD_OVERLOAD make_perspective_projection_matrix4x4(
    const radians fov, const float aspect_ratio, const float near_z,
    const float far_z) {
  const float ys = 1 / std::tan(fov * 0.5f);
  const float xs = ys / aspect_ratio;

  return make_matrix4x4(xs, 0, 0, 0, 0, ys, 0, 0, 0, 0,
                        far_z / (far_z - near_z),
                        -(near_z * far_z) / (far_z - near_z), 0, 0, -1, 0);
}

} // namespace apple_math