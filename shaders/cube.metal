#include <metal_stdlib>

#include "objects/primitives/data.h"

using namespace metal;

struct Vertex_Out {
  vector_float4 position [[ position ]];
  vector_float2 texture_coordinate;
};

vertex Vertex_Out
vertex_shader(uint vertex_id [[ vertex_id ]],
              constant Vertex *verticies [[ buffer(0) ]],
              constant matrix_float4x4 *clip_matrix [[ buffer(1) ]]) {
  Vertex_Out out;
  out.position = *clip_matrix *
                 verticies[vertex_id].position;
  out.texture_coordinate = verticies[vertex_id].texture_coordinate;

  return out;
}

fragment vector_float4 fragment_shader(Vertex_Out in [[ stage_in ]],
                                       texture2d<float> color_texture
                                       [[ texture(0) ]]) {
  constexpr sampler texture_sampler(mag_filter::linear, min_filter::linear);
  const vector_float4 color_sample =
      color_texture.sample(texture_sampler, in.texture_coordinate);

  return color_sample;
}