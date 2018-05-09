#include "window.h"

#include "GLFW/glfw3.h"

Window::Window(const glm::ivec2& size, const char* title, const WindowContextHints& hints) {}

Window::~Window()
{
    if (m_window)
    {
        glfwDestroyWindow(m_window);
    }
}
