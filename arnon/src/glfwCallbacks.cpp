#include "glfwCallbacks.h"
#include "inputManager.h"
#include "debug/arnlog.h"

#include "GLFW/glfw3.h"
#include "imgui/imgui.h"

// ImGui extern for input management
extern bool g_MouseJustPressed[3];

// Global Input Manager Instance
extern InputManager g_inputManager;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    ImGuiIO& io = ImGui::GetIO();
    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        if (!io.WantCaptureKeyboard) // If ImGui is not reserving input
            g_inputManager.pressKey(key);
        io.KeysDown[key] = true; // ImGui
        logDebug("Pressed key: {}", key);
    }
    else if (action == GLFW_RELEASE)
    {
        g_inputManager.releaseKey(key);
        io.KeysDown[key] = false; // ImGui
        logDebug("Released key: {}", key);
    }

    (void)mods; // Modifiers are not reliable across systems
    io.KeyCtrl  = io.KeysDown[GLFW_KEY_LEFT_CONTROL]|| io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
    io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT]  || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
    io.KeyAlt   = io.KeysDown[GLFW_KEY_LEFT_ALT]    || io.KeysDown[GLFW_KEY_RIGHT_ALT];
    io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER]  || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    ImGuiIO& io = ImGui::GetIO();

    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        if (!io.WantCaptureMouse) // If ImGui is not reserving input
            g_inputManager.pressKey(button);
        logDebug("Pressed mouse button: {}", button);

        // ImGui Interaction
        if (button >= 0 && button < 3)
            g_MouseJustPressed[button] = true;
    }
    else if (action == GLFW_RELEASE)
    {
        g_inputManager.releaseKey(button);
        logDebug("Released mouse button: {}", button);
    }
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    g_inputManager.moveCursor(glm::dvec2{ xpos, ypos });
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    g_inputManager.scrollMouse({ xoffset, yoffset });
    logDebug("Scrolldelta on Y-Axis: {}", yoffset);

    // ImGui Interaction
    ImGuiIO& io = ImGui::GetIO();
    io.MouseWheel += (float)yoffset;
}

void error_callback(int error, const char* description)
{
    logErr("GLFW Error #{}: {}", error, description);
}
