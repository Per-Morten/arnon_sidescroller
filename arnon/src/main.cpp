#include <iostream>

#include "GL/glCore45.h"
#include "GLFW/glfw3.h"

int main()
{
    glfwInit();
    
    auto* window = glfwCreateWindow(1280, 720, "Test Compile", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    gl::sys::LoadFunctions();

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        gl::Clear(gl::COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
    }

    return 0;
}
