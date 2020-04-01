#include "Window.hpp"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace coffee
{

GLFWwindow *initWindow(const WindowInfo &info)
{
    if (!glfwInit()) {
        std::cerr << "ERROR Loading GLFW" << std::endl;
        glfwTerminate();
        std::exit(1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, info.isResizable);

    GLFWwindow *window = glfwCreateWindow(info.size.x, info.size.y, info.title.c_str(), NULL, NULL);
    if (!window) {
        std::cerr << "ERROR Creating GL Context" << std::endl;
        glfwTerminate();
        std::exit(1);
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cerr << "ERROR Failed to initialize OpenGL context" << std::endl;
        glfwTerminate();
        std::exit(1);
    }

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

    return window;
}

}