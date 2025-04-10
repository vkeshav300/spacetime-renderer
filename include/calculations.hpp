#pragma once

#include "unit.hpp"
#include "renderer/color.h"

#define APPLE_SIMD_OVERLOAD __attribute__((__overloadable__))

#include <simd/simd.h>

using radians = float;

namespace apple_math {
matrix_float4x4 APPLE_SIMD_OVERLOAD make_matrix4x4(
    const float m00, const float m01, const float m02, const float m03,
    const float m10, const float m11, const float m12, const float m13,
    const float m20, const float m21, const float m22, const float m23,
    const float m30, const float m31, const float m32, const float m33);

matrix_float4x4 APPLE_SIMD_OVERLOAD make_translation_matrix4x4(const float x,
                                                               const float y,
                                                               const float z);

matrix_float4x4 APPLE_SIMD_OVERLOAD
make_translation_matrix4x4(const vector_float3 &translations);

matrix_float4x4 APPLE_SIMD_OVERLOAD make_rotation_matrix4x4(const radians theta,
                                                            vector_float3 axis);

matrix_float4x4 APPLE_SIMD_OVERLOAD
make_rotation_matrix4x4(const vector_float4 &rotations);

matrix_float4x4 APPLE_SIMD_OVERLOAD make_look_at_matrix4x4(
    const vector_float3 &position, const vector_float3 &target);

matrix_float4x4 APPLE_SIMD_OVERLOAD make_perspective_projection_matrix4x4(
    const radians fov, const float aspect_ratio, const float near_z,
    const float far_z);

matrix_float4x4 APPLE_SIMD_OVERLOAD make_identity_matrix4x4();
} // namespace apple_math

namespace blackbodies {
constexpr float wiens_constant = 2.898e-3f;
constexpr float rgb_intensity_max = 255.0f;
constexpr float rgb_gamma = 0.80f;

Unit get_peak_wavelength(const Unit &temperature);

Color get_rgba_from_wavelength(const Unit &lambda);
} // namespace blackbodies
