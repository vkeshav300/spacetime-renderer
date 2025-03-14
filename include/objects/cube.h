#pragma once

#include "data.h"
#include "object.h"

#include <vector>

class Cube : public Object {
public:
  std::vector<Vertex> m_verticies;
  Transformations m_transformations;

public:
  Cube(const vector_float3 &translations, const float rotation_magnitude,
       const vector_float3 &rotation_axis);
  ~Cube();
};