#include "objects/primitives/triangle.hpp"

#include <simd/simd.h>

Triangle::Triangle() {}

Triangle::~Triangle() {
    delete m_texture;
}