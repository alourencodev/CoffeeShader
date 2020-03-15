#include "Context.hpp"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace coffee::context
{

static const char k_windowTitle[] = "Coffee Shader";
static const uint32_t screenWidth = 2560;
static const uint32_t screenHeight = 1440;

static GLFWwindow *s_window = nullptr;

void init()
{
    if (!glfwInit()) {
        std::cerr << "ERROR Loading GLFW" << std::endl;
        glfwTerminate();
        std::exit(1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    s_window = glfwCreateWindow(screenWidth, screenHeight, k_windowTitle, NULL, NULL);
    if (!s_window) {
        std::cerr << "ERROR Creating GL Context" << std::endl;
        glfwTerminate();
        std::exit(1);
    }

    glfwMakeContextCurrent(s_window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cerr << "ERROR Failed to initialize OpenGL context" << std::endl;
        glfwTerminate();
        std::exit(1);
    }

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
}

bool update()
{
    if (glfwWindowShouldClose(s_window)) {
        return false;
    }

    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(s_window);

    return true;
}

void terminate()
{
    glfwDestroyWindow(s_window);
    glfwTerminate();
}

}