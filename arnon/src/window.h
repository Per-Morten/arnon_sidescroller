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
    uint8_t openGLMajor = 4;     // Major OpenGL Version
    uint8_t openGLMinor = 5;     // Minor OpenGL Version
    uint8_t samples     = 1;     // Number of samples

    bool useCoreProfile = true;  // False means compat profile
    bool decorated      = true;  // Borders etc.
    bool visible        = true;  
    bool resizeable     = true;
    bool fullscreen     = false;
    bool alwaysOnTop    = false; // Always be on top of other windows
    bool debugContext   = false; // Enable OpenGL debug context or not
};

class Window
{
private:
    // The GLFW window managed
    GLFWwindow* m_window = nullptr;

    // The window size
    glm::ivec2 m_size;

public:
    Window(const glm::ivec2& size, const char* title, const WindowContextHints& hints = {});

    ~Window();

    // Resize window
    void resize(const glm::ivec2& size);

    // Hide the window
    void hide() const;

    // Show the window
    void show() const;

    // Set the fullscreen status of the window
    void setFullscreen(const bool flag);

    // Make the GL Context Current
    void setContextAsCurrent();

    // Get the size of the window
    const glm::vec2& getSize() const;

    // Get underlying GLFWwindow pointer (Consider implicit conversion?)
    const GLFWwindow* get() const;
    GLFWwindow* get();
};

#endif  // WINDOW_H
