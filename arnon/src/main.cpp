#include "window.h"

#include "GL/glCore45.h"
#include "GLFW/glfw3.h"

int main()
{
    glfwInit();

    auto window = Window({1280, 720}, "Test");
    glfwMakeContextCurrent(window.get());

    gl::sys::LoadFunctions();

    while (!glfwWindowShouldClose(window.get()))
    {
        glfwPollEvents();
        gl::Clear(gl::COLOR_BUFFER_BIT);
        glfwSwapBuffers(window.get());
    }

    return 0;
}
