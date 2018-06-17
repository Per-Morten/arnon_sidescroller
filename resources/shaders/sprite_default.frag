// ArnonSidescroller default Fragment Shader for sprites
#version 450 core

layout(location = 0) out vec4 color;

// Uniforms
layout(location=1, binding=0) uniform sampler2D diffuseTex;
layout(location=2, binding=1) uniform sampler2D normalTex;

// From Vertex Shader
in vtx_block
{
        vec4 position;
        vec4 color;
        vec2 texCoord;
} vtx;

void main()
{
        color = vtx.color;
}
