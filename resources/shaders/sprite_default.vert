// ArnonSidescroller default Vertex Shader for sprites
#version 450 core

// VTX Attributes
layout(location=0) in vec3 a_position;
layout(location=1) in vec2 a_texCoord;
layout(location=2) in vec4 a_color;

// Uniforms
layout(location=0) uniform mat4 mvpMatrix = mat4(1.f);

// For future shader stages
out vtx_block
{
        vec4 position;
        vec4 color;
        vec2 texCoord;
} vtx;

void main()
{
        vtx.position = mvpMatrix * vec4(a_position, 1.f);
        vtx.color = a_color;
        vtx.texCoord = a_texCoord;

        gl_Position = vtx.position;
}
