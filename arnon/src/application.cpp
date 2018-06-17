#include "application.h"
#include "clock.h"
#include "debug/arnlog.h"
#include "GL/glCallbacks.h"
#include "scene_mainMenu.h"

#include "GL/glCore45.h"
#include "GLFW/glfw3.h"
#include "imgui/imgui.h"
#include "imgui/imgui_glfw.h"

Application::Application()
{
    gl::sys::LoadFunctions();

// Use OpenGL Debug callback in debug mode
#ifndef NDEBUG
    gl::DebugMessageCallback(glDebugCallback, nullptr);
    gl::DebugMessageControl(gl::DONT_CARE, gl::DONT_CARE, gl::DONT_CARE, 0, nullptr, true);
#endif

    m_imguiContext = ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(m_window.get());

    // Add the main menu
    m_sceneManager.pushScene(std::make_unique<SMainMenu>(m_sceneManager));
}

Application::~Application()
{
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
}

void Application::run()
{
    Stopwatch deltaClock;

    // #TODO : Possibly improve the main loop to fixed step updating and
    // free drawing? Right now it's about as basic as it gets at least.
    while (!glfwWindowShouldClose(m_window.get()))
    {
        const auto deltaTime = deltaClock.restart().count();
        glfwPollEvents();
        preUpdate();
        update(deltaTime);
        postUpdate();
        draw();
    }
}

void Application::preUpdate()
{
    ImGui_ImplGlfwGL3_NewFrame();
}

void Application::update(const float dt)
{
    // Stats
    ImGui::Begin("Stats");
    ImGui::Text("FPS: %.2f", 1.f / dt);
    ImGui::End();

    // Settings Menu
    ImGui::Begin("Settings");
    if (ImGui::Checkbox("Vsync Enabled", &m_settings.VsyncEnabled))
    {
        glfwSwapInterval(m_settings.VsyncEnabled);
    }
    ImGui::End();
    
    m_sceneManager.update(dt);
}

void Application::postUpdate()
{

}

void Application::draw()
{
    gl::Clear(gl::COLOR_BUFFER_BIT);

    // Rendering code goes here

    ImGui::Render();
    ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(m_window.get());
}
