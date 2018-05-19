#include "window.h"
#include "arnlog/arnlog.h"

#include "GL/glCore45.h"
#include "GLFW/glfw3.h"

Window::Window(const glm::ivec2& size, const char* title, const WindowContextHints& hints) : m_size(size)
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

    m_window = glfwCreateWindow(size.x, size.y, title, (hints.fullscreen ? glfwGetPrimaryMonitor() : nullptr), nullptr);
    
    // #NOTE : Consider throwing on failure
    if (!m_window)
    {
        logErr("Failed to create GLFW Window!");
    }

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
    m_size = size;
    glfwSetWindowSize(m_window, size.x, size.y);
}

void Window::hide() const
{
    if(m_window) glfwHideWindow(m_window);
}

void Window::show() const
{
    if (m_window) glfwShowWindow(m_window);
}

void Window::setFullscreen(const bool flag)
{
    if (m_window)
    {
        // Gather monitor information
        auto* monitor = glfwGetPrimaryMonitor();
        auto videoMode = glfwGetVideoMode(monitor);

        // Set based on flag
        m_size = { videoMode->width, videoMode->height };
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

const glm::vec2 Window::getSize() const
{
    return m_size;
}

const GLFWwindow* Window::get() const { return m_window; }

GLFWwindow* Window::get() { return m_window; }
