#include "window.h"
#include "application.h"
#include "inputManager.h"

#include "GLFW/glfw3.h"

#ifndef NDEBUG
#define ARN_ASSERT_TERMINATE // Only log in debug mode
#endif

// A global Input Manager Instance
InputManager g_inputManager;

int main()
{
    glfwInit();

    Application arnonSidescroller;
    arnonSidescroller.run();

    glfwTerminate();
    return 0;
}
