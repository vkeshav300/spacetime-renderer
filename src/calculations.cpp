#include "calculations.hpp"

#include <algorithm>
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
    return make_identity_matrix4x4();

  axis = simd_normalize(axis);

  const float ct = std::cosf(theta), st = std::sinf(theta), ci = 1 - ct,
              x = axis.x, y = axis.y, z = axis.z;

  return make_matrix4x4(
      x * x * ci + ct, x * y * ci - z * st, x * z * ci + y * st, 0,
      x * y * ci + z * st, y * y * ci + ct, y * z * ci - x * st, 0,
      x * z * ci - y * st, y * z * ci + x * st, z * z * ci + ct, 0, 0, 0, 0, 1);
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
                      u = simd_cross(f, r);

  return make_matrix4x4(r.x, u.x, f.x, 0, r.y, u.y, f.y, 0, r.z, u.z, f.z, 0,
                        -simd_dot(r, position), -simd_dot(u, position),
                        -simd_dot(f, position), 1);
}

matrix_float4x4 APPLE_SIMD_OVERLOAD make_perspective_projection_matrix4x4(
    const radians fov, const float aspect_ratio, const float near_z,
    const float far_z) {
  const float ys = 1 / std::tan(fov * 0.5f), xs = ys / aspect_ratio,
              zs = far_z / (far_z - near_z), zn = -near_z * zs;

  return make_matrix4x4(xs, 0, 0, 0, 0, ys, 0, 0, 0, 0, zs, 1, 0, 0, zn, 0);
}

matrix_float4x4 APPLE_SIMD_OVERLOAD make_identity_matrix4x4() {
  return make_matrix4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
}
} // namespace apple_math

namespace physics {

namespace blackbodies {
Unit get_peak_wavelength(const Unit &temperature) {
  return Unit(1e9f * wiens_constant / temperature.get_value());
}

Color get_rgba_from_wavelength(const Unit &lambda) {
  /* It is important to note that this function calculates the RGBA for a given
   * wavelength, not a blackbody curve with the wavelength being the peak of the
   * curve */
  Color color;

  /* Calculate rgb */
  if (lambda >= 380.0_nm && lambda < 440.0_nm) {
    color.r = (-(lambda - 440.0_nm) / 60.0).get_value();
    color.g = 0.0f;
    color.b = 1.0f;
  } else if (lambda >= 440.0_nm && lambda < 490.0_nm) {
    color.r = 0.0f;
    color.g = ((lambda - 440.0_nm) / 50.0f).get_value();
    color.b = 1.0f;
  } else if (lambda >= 490.0_nm && lambda < 510.0_nm) {
    color.r = 0.0f;
    color.g = 1.0f;
    color.b = (-(lambda - 510.0_nm) / 20.0f).get_value();
  } else if (lambda >= 510.0_nm && lambda < 580.0_nm) {
    color.r = ((lambda - 510.0_nm) / 70.0f).get_value();
    color.g = 1.0f;
    color.b = 0.0f;
  } else if (lambda >= 580.0_nm && lambda < 645.0_nm) {
    color.r = 1.0f;
    color.g = (-(lambda - 645.0_nm) / 65.0f).get_value();
    color.b = 0.0f;
  } else if (lambda >= 645.0_nm && lambda < 781.0_nm) {
    color.r = 1.0f;
    color.b = 0.0f;
    color.g = 0.0f;
  } else {
    color.r = 0.0f;
    color.b = 0.0f;
    color.g = 0.0f;
  }

  float factor;
  const float lambda_f = lambda.get_value();

  /* Account for intensity falloff near vision limits */
  if (lambda >= 380.0_nm && lambda < 420.0_nm)
    factor = 0.3f + 0.7f * (lambda_f - 380.0f) / 40.0f;
  else if (lambda >= 420.0_nm && lambda < 701.0_nm)
    factor = 1.0f;
  else if (lambda >= 701.0_nm && lambda < 781.0_nm)
    factor = 0.3f + 0.7f * (780.0f - lambda_f) / 80.0f;
  else
    factor = 0.0f;

  color.r = color.r == 0.0f
                ? 0.0f
                : rgb_intensity_max * pow(color.r * factor, rgb_gamma);
  color.g = color.g == 0.0f
                ? 0.0f
                : rgb_intensity_max * pow(color.g * factor, rgb_gamma);
  color.b = color.b == 0.0f
                ? 0.0f
                : rgb_intensity_max * pow(color.b * factor, rgb_gamma);
  color.a = 1.0f;

  /* Clamp values from rgb range [0, 255] */
  color.r = std::clamp<float>(color.r, 0.0f, 255.0f);
  color.g = std::clamp<float>(color.g, 0.0f, 255.0f);
  color.b = std::clamp<float>(color.b, 0.0f, 255.0f);

  return color;
}
} // namespace blackbodies

} // namespace physics
