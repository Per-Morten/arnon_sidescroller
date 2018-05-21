#include "window.h"
#include "scene.h"
#include "scene_mainMenu.h"
#include "scene_optionsMenu.h"
#include "sceneManager.h"
#include "inputManager.h"
#include "glfwCallbacks.h"
#include "debug/arnlog.h"
#include "debug/asserts.h"
#include "GL/framebuffer.h"
#include "GL/shaderObject.h"
#include "GL/shaderProgram.h"
#include "GL/shape2D_quad.h"

#include <string>

#include "imgui/imgui.h"
#include "imgui/imgui_glfw.h"
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

// A global Input Manager Instance
InputManager g_inputManager;

int main()
{
    glfwInit();

    auto window = Window({ 1280, 720 }, "Test");
    glfwMakeContextCurrent(window.get());

    glfwSetCursorPosCallback(window.get(), cursor_position_callback);
    glfwSetKeyCallback(window.get(), key_callback);
    glfwSetScrollCallback(window.get(), scroll_callback);
    glfwSetMouseButtonCallback(window.get(), mouse_button_callback);

    gl::sys::LoadFunctions();

    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(window.get());

    SceneManager sm;

    sm.pushScene(std::make_unique<SMainMenu>(sm));
    sm.pushScene(std::make_unique<SOptionsMenu>(sm));

    while (!glfwWindowShouldClose(window.get()))
    {
        glfwPollEvents();
        ImGui_ImplGlfwGL3_NewFrame();

        sm.update(1.f / 144.f);

        ImGui::Text("Hello World");

        gl::Clear(gl::COLOR_BUFFER_BIT);

        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window.get());
    }

    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}
