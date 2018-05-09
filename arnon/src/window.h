/*
 * The Window class wraps a GLFW Window and handles
 * resizing etc.
 */

#ifndef WINDOW_H
#define WINDOW_H

#include "glm/vec2.hpp"

struct GLFWwindow;

struct WindowContextHints
{
    int OpenGLMajor = 4;
    int OpenGLMinor = 5;
    int Multisampling = 1;
    int Resizeable = 1;
    int GLProfile = 1;
};

class Window
{
private:
    // The GLFW window managed
    GLFWwindow* m_window = nullptr;

public:
    Window(const glm::ivec2& size, const char* title, const WindowContextHints& hints = {});

    ~Window();

};

#endif  // WINDOW_H
