#include "window.h"
#include "arnlog/arnlog.h"
#include "GL/framebuffer.h"
#include "GL/shaderObject.h"
#include "GL/shaderProgram.h"
#include "GL/shape2D_quad.h"

#include <string>

#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "GL/glCore45.h"
#include "GLFW/glfw3.h"

// For testing
const std::string vertexShader =
R"(
#version 450 core
layout(location = 0) in vec2 aPosition;
layout(location = 1) in vec2 aTexCoord;
layout(location = 2) in vec4 aColor;

layout(location = 0) uniform mat4 uModelViewController = mat4(1.f);

out vec4 vs_color;
out vec2 vs_texCoord;

void main()
{
    gl_Position = uModelViewController * vec4(aPosition, 0, 1.f);
    vs_color = aColor;
    vs_texCoord = aTexCoord;
}
)";

// For testing
const std::string fragmentShader =
R"(
#version 450 core
out vec4 color;

in vec4 vs_color;
in vec2 vs_texCoord;

void main()
{
    color = vs_color;
}
)";

// For testing
const std::string glowFragment =
R"(
#version 450 core
out vec4 color;

in vec4 vs_color;
in vec2 vs_texCoord;

layout(location = 1) uniform sampler2D sampla;

const int radius = 64;

void main()
{
    vec4 outCol = vec4(vec3(0.f), 1.f);

    // Sample every 4th pixel
    for(int x = -radius; x < radius; x += 4)
    {
        for(int y = -radius; y < radius; y += 4)
        {
            // Multiply by the distance from fragment sample to get falloff
            const vec4 smpl = texture(sampla, vs_texCoord + vec2(x / 1600.f, y / 900.f));
            outCol += smpl * ((radius / 900.f) - distance(vs_texCoord, vs_texCoord - vec2(x / 1600.f, y / 900.f)));
        }
    }

    // Average the color
    outCol /= radius * 0.5f;
    color = texture(sampla, vs_texCoord) + vec4(outCol.rgb, 1.f);
}
)";

int main()
{
    glfwInit();

    auto window = Window({ 1280, 720 }, "Test");
    glfwMakeContextCurrent(window.get());

    gl::sys::LoadFunctions();

    logDebug("Hello {} how are your ${:.2f} doing?", "Bjarne", 24.61);
    logInfo("May I steal your {1} anal holes, {0}?", "John", "fine");
    logWarn("Hello {:^32} this is centered!", "[CENTERED MESSAGE]");
    logErr("This is a {errorType} error! Made by {name} of {kingdom}", fmt::arg("name", "Carl"), fmt::arg("kingdom", "Moravia"), fmt::arg("errorType", "nullptr"));

    // Construct Shader
    ShaderObject vs(vertexShader, EShaderType::VertexShader);
    ShaderObject fs(fragmentShader, EShaderType::FragmentShader);
    ShaderObject fs2(glowFragment, EShaderType::FragmentShader);

    ShaderProgram program(vs, fs);
    ShaderProgram postProcessProgram(vs, fs2);

    // Set Projection and Model Uniform
    const auto mvpMat = glm::ortho(0.f, 1280.f, 0.f, 720.f, -1.f, 1.f) * glm::translate(glm::mat4(1.f), glm::vec3(640.f, 360.f, 0.f));

    Framebuffer framebuffer({ 1280.f, 720.f });

    // For test rendering
    Quad testQuad({ 360.f, 360.f });

    // Covers entire screen
    Quad screenQuad({ 2.f, 2.f });

    while (!glfwWindowShouldClose(window.get()))
    {
        glfwPollEvents();
        gl::Clear(gl::COLOR_BUFFER_BIT);

        // Draw the quad to the framebuffer
        framebuffer.bind();
        program.bind();
        gl::UniformMatrix4fv(0, 1, gl::FALSE_, glm::value_ptr(mvpMat));
        testQuad.draw(program);
        framebuffer.unbind();

        // Draw the framebuffer to the screen using the screenQuad and a glow
        postProcessProgram.bind();
        framebuffer.bindTexture(0);
        gl::Uniform1i(1, 0);
        screenQuad.draw(postProcessProgram);
        framebuffer.unbindTexture(0);

        glfwSwapBuffers(window.get());
    }

    glfwTerminate();
    return 0;
}
