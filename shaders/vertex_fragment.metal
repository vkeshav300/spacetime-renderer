#include "renderer/gpu_buffers.hpp"

#include <metal_stdlib>

using namespace metal;

struct Vertex_Out {
    vector_float4 position [[ position ]];
    vector_float2 texture_coordinate;
    bool textured;
    Color color;
};

vertex Vertex_Out vertex_shader(const uint vertex_ID [[ vertex_id ]], constant Vertex *verticies [[ buffer(0) ]], constant Transformations *transformations [[ buffer(1) ]], constant Appearance *appearance [[ buffer(2) ]]) {
    Vertex_Out out;
    out.position = transformations->clip_matrix * verticies[vertex_ID].position;
    out.texture_coordinate = verticies[vertex_ID].texture_coordinate;
    out.textured = appearance->textured;
    out.color = appearance->color;

    return out;
}

fragment vector_float4 fragment_shader(Vertex_Out in [[ stage_in ]], texture2d<float> color_texture [[ texture(0) ]]) {
    if (in.textured) {
        constexpr sampler texture_sampler(mag_filter::linear, min_filter::linear);
        return color_texture.sample(texture_sampler, in.texture_coordinate);
    }

    return vector_float4{in.color.r, in.color.b, in.color.g, in.color.a};
}
