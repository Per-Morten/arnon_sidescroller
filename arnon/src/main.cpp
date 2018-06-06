#include "window.h"
#include "debug/arnlog.h"
#include "debug/asserts.h"
#include "GL/framebuffer.h"
#include "GL/shaderObject.h"
#include "GL/shaderProgram.h"
#include "GL/shape2D_quad.h"

#include <string>

#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "GL/glCore45.h"
#include "GLFW/glfw3.h"

#ifndef NDEBUG
#define ARN_ASSERT_TERMINATE // Only log in debug mode
#endif

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


int main()
{
    glfwInit();

    auto window = Window({ 1280, 720 }, "Test");
    glfwMakeContextCurrent(window.get());

    gl::sys::LoadFunctions();

    while (!glfwWindowShouldClose(window.get()))
    {
        glfwPollEvents();
        gl::Clear(gl::COLOR_BUFFER_BIT);



        glfwSwapBuffers(window.get());
    }

    glfwTerminate();
    return 0;
}
