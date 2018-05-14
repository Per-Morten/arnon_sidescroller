#include "window.h"
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

void main()
{
    gl_Position = uModelViewController * vec4(aPosition, 0, 1.f);
    vs_color = aColor;
}
)";

// For testing
const std::string fragmentShader =
R"(
#version 450 core
out vec4 color;

in vec4 vs_color;

void main()
{
    color = vs_color;
}
)";

int main()
{
    glfwInit();

    auto window = Window({1280, 720}, "Test");
    glfwMakeContextCurrent(window.get());

    gl::sys::LoadFunctions();

    // Construct Shader
    ShaderObject vs(vertexShader, EShaderType::VertexShader);
    ShaderObject fs(fragmentShader, EShaderType::FragmentShader);    
    ShaderProgram program(vs, fs);

    // Set Projection and Model Uniform
    const auto mvpMat = glm::ortho(0.f, 1280.f, 0.f, 720.f, -1.f, 1.f) * glm::translate(glm::mat4(1.f), glm::vec3(640.f, 360.f, 0.f));
    program.bind();
    gl::UniformMatrix4fv(0, 1, gl::FALSE_, glm::value_ptr(mvpMat));

    Quad testQuad({ 100.f, 100.f });

    while (!glfwWindowShouldClose(window.get()))
    {
        glfwPollEvents();
        gl::Clear(gl::COLOR_BUFFER_BIT);

        testQuad.draw(program);

        glfwSwapBuffers(window.get());
    }

    return 0;
}
