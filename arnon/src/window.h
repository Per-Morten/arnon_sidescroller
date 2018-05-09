/*
 * The Window class wraps a GLFW Window and handles
 * resizing etc.
 */

#ifndef WINDOW_H
#define WINDOW_H

#include "glm/vec2.hpp"

struct GLFWwindow;

// Contains various options for the OpenGL context creation
struct WindowContextHints
{
    int OpenGLMajor = 4;    // Major OpenGL Version
    int OpenGLMinor = 5;    // Minor OpenGL Version
    int Multisampling = 1;  // Number of samples
    int Resizeable = 1;     // 1 = Yes, 0 = No
    int GLProfile = 1;      // 1 = Core, 0 = Compat
    int fullscreen = 0;     // 1 = Yes, 0 = No
};

class Window
{
private:
    // The GLFW window managed
    GLFWwindow* m_window = nullptr;

public:
    Window(const glm::ivec2& size, const char* title, const WindowContextHints& hints = {});

    ~Window();

    // Make the GL Context Current
    void setContextAsCurrent();

    // Get underlying GLFWwindow pointer (Consider implicit conversion?)
    const GLFWwindow* get() const;
    GLFWwindow* get();
};

#endif  // WINDOW_H
