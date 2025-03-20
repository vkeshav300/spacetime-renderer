#include "objects/primitives/triangle.hpp"

#include <simd/simd.h>

Triangle::Triangle()
    : m_verticies({{{-0.5f, -0.5f, 0.0f, 1.0f}, {0.0f, 0.0f}},
                   {{0.5f, -0.5f, 0.0f, 1.0f}, {1.0f, 0.0f}},
                   {{0.0f, 0.5f, 0.0f, 1.0f}, {0.5f, 1.0f}}}) {}

Triangle::~Triangle() {}