#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

static GLFWwindow *g_window = nullptr;

static void init()
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

    g_window = glfwCreateWindow(1440, 1080, "Coffee Shader", NULL, NULL);
    if (!g_window) {
        std::cerr << "ERROR Creating GL Context" << std::endl;
        glfwTerminate();
        std::exit(1);
    }

    glfwMakeContextCurrent(g_window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cerr << "ERROR Failed to initialize OpenGL context" << std::endl;
        glfwTerminate();
        std::exit(1);
    }

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
}

static void update()
{
    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(g_window);
}

static void terminate()
{
    glfwDestroyWindow(g_window);
    glfwTerminate();
}

int main()
{
    init();
    
    while (!glfwWindowShouldClose(g_window)) {
        update();
    }

    terminate();

    return 0;
}