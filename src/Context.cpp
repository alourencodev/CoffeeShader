#include "Context.hpp"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace coffee::context
{

static const char k_windowTitle[] = "Coffee Shader";
static const uint32_t s_windowWidth = 2560;
static const uint32_t s_windowHeight = 1440;

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

    GLFWwindow *window = glfwCreateWindow(s_windowWidth, s_windowHeight, k_windowTitle, NULL, NULL);
    if (!window) {
        std::cerr << "ERROR Creating GL Context" << std::endl;
        glfwTerminate();
        std::exit(1);
    }

    glfwMakeContextCurrent(window);
    ContextData::get().window = window;
    ContextData::get().windowSize =  glm::ivec2(s_windowWidth, s_windowHeight);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cerr << "ERROR Failed to initialize OpenGL context" << std::endl;
        glfwTerminate();
        std::exit(1);
    }

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
}

bool update()
{
    GLFWwindow *window = ContextData::get().window;
    if (glfwWindowShouldClose(window)) {
        return false;
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT);

    return true;
}

void terminate()
{
    glfwDestroyWindow(ContextData::get().window);
    glfwTerminate();
}

}