/// ArnonSidescroller

#ifndef GLFW_CALLBACKS_H
#define GLFW_CALLBACKS_H

struct GLFWwindow;

// GLFW Key Callback
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

// GLFW Mouse Button Callback
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

// GLFW Cursor Position Callback
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

// GLFW Mouse Scroll Wheel Callback
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// GLFW Error Callback
void error_callback(int error, const char* description);

#endif // GLFW_CALLBACKS_H
