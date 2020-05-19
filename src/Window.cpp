#include "Window.hpp"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Utils/Log.hpp"

namespace coffee::window
{

constexpr char k_logTag[] = "Window";

static void glErrorLog(const char *name, void *funcPtr, int rgsLength, ...)
{
    GLenum error_code;
    error_code = glad_glGetError();

    if (error_code != GL_NO_ERROR) {
        // TODO: Have error namings
        logError("GL", "Error %d in %s.", error_code, name);
    }
}

GLFWwindow *create(const Info &info)
{
    if (!glfwInit()) {
        glfwTerminate();
        logFatal(k_logTag, "Unable to initialize GLFW.");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, info.isResizable);

    GLFWwindow *window = glfwCreateWindow(info.size.x, info.size.y, info.title.c_str(), NULL, NULL);
    if (!window) {
        glfwTerminate();
        logFatal(k_logTag, "Unable to create GL Context.");
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        glfwTerminate();
        logFatal(k_logTag, "Unable to initialize GL Context.");
    }

    glad_set_post_callback(glErrorLog);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

    return window;
}

}