#include "renderer/gpu_buffers.h"

#include <metal_stdlib>

using namespace metal;

struct Vertex_Out {
    vector_float4 position [[ position ]];
    vector_float2 texture_coordinate;
};

vertex Vertex_Out vertex_shader(const uint vertex_ID [[ vertex_id ]], constant Vertex *verticies [[ buffer(0) ]]) {
    Vertex_Out out;
    out.position = verticies[vertex_ID].position;
    out.texture_coordinate = verticies[vertex_ID].texture_coordinate;

    return out;
}

fragment vector_float4 fragment_shader(Vertex_Out in [[ stage_in ]]) {
    return float4(182.0f/255.0f, 240.0f/255.0f, 228.0f/255.0f, 1.0f);
}