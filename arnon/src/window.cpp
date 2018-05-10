#include "window.h"

#include "GL/glCore45.h"
#include "GLFW/glfw3.h"

Window::Window(const glm::ivec2& size, const char* title, const WindowContextHints& hints)
{
    // Set Window Hints
    glfwWindowHint(GLFW_OPENGL_PROFILE, (hints.useCoreProfile ? GLFW_OPENGL_CORE_PROFILE : GLFW_OPENGL_COMPAT_PROFILE));
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, hints.openGLMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, hints.openGLMinor);
    glfwWindowHint(GLFW_SAMPLES, hints.samples);
    glfwWindowHint(GLFW_DECORATED, hints.decorated);
    glfwWindowHint(GLFW_FLOATING, hints.alwaysOnTop);
    glfwWindowHint(GLFW_VISIBLE, hints.visible);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, hints.debugContext);
    glfwWindowHint(GLFW_RESIZABLE, hints.resizeable);

    // #TODO : Error log if window failed to create!
    m_window = glfwCreateWindow(size.x, size.y, title, (hints.fullscreen ? glfwGetPrimaryMonitor() : nullptr), nullptr);
    setContextAsCurrent();
}

Window::~Window()
{
    if (m_window)
    {
        glfwDestroyWindow(m_window);
    }
}

void Window::resize(const glm::ivec2& size)
{
    glfwSetWindowSize(m_window, size.x, size.y);
}

void Window::setFullscreen(const bool flag)
{
    if (m_window)
    {
        // Gather monitor information
        auto* monitor = glfwGetPrimaryMonitor();
        auto videoMode = glfwGetVideoMode(monitor);

        // Set based on flag
        glfwSetWindowMonitor(m_window, (flag ? glfwGetPrimaryMonitor() : nullptr), 0, 0, videoMode->width,
                             videoMode->height, videoMode->refreshRate);
    }
}

void Window::setContextAsCurrent()
{
    if (m_window)
    {
        glfwMakeContextCurrent(m_window);
    }
}

const GLFWwindow* Window::get() const { return m_window; }

GLFWwindow* Window::get() { return m_window; }