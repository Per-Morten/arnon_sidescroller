#include "application.h"

#include "GL/glCore45.h"
#include "GLFW/glfw3.h"
#include "imgui/imgui.h"
#include "imgui/imgui_glfw.h"

Application::Application()
{
    gl::sys::LoadFunctions();

    m_imguiContext = ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(m_window.get());

}

Application::~Application()
{
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
}

void Application::run()
{
    while (!glfwWindowShouldClose(m_window.get()))
    {
        glfwPollEvents();
        update(0.15f);
        draw();
    }
}

void Application::update(const float dt)
{
    ImGui_ImplGlfwGL3_NewFrame();

    m_sceneManager.update(dt);
}

void Application::draw()
{
    gl::Clear(gl::COLOR_BUFFER_BIT);


    ImGui::Render();
    ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(m_window.get());
}
