#include "window.h"

#include "GLFW/glfw3.h"

Window::Window(const glm::ivec2& size, const char* title, const WindowContextHints& hints)
{
    // Set Window Hints
    glfwWindowHint(GLFW_OPENGL_PROFILE, (hints.GLProfile == 1 ? GLFW_OPENGL_CORE_PROFILE : GLFW_OPENGL_COMPAT_PROFILE));
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, hints.OpenGLMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, hints.OpenGLMinor);
    glfwWindowHint(GLFW_RESIZABLE, hints.Resizeable);

    // #TODO : Error log if window failed to create!
    m_window = glfwCreateWindow(size.x, size.y, title,
                               (hints.fullscreen ? glfwGetPrimaryMonitor() : nullptr), nullptr);
    setContextAsCurrent();
}

Window::~Window()
{
    if (m_window)
    {
        glfwDestroyWindow(m_window);
    }
}

void Window::setContextAsCurrent()
{
    if (m_window)
    {
        glfwMakeContextCurrent(m_window);
    }
}

const GLFWwindow*Window::get() const
{
    return m_window;
}

GLFWwindow*Window::get()
{
    return m_window;
}
