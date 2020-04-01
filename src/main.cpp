#include <GLFW/glfw3.h>

#include "Canvas.hpp"
#include "ShaderSystem.hpp"
#include "Window.hpp"

using namespace coffee;

constexpr char k_windowTitle[] = "Coffee Shader";
static const glm::ivec2 s_windowSize = {2560, 1440};

static GLFWwindow *s_window;

int main()
{
    auto init = []() -> void
    {
        WindowInfo windowInfo = {};
        windowInfo.title = k_windowTitle;
        windowInfo.size = s_windowSize;

        s_window = initWindow(windowInfo);

        shaderSystem::setShader("shaders/default.glsl.vert", "shaders/default.glsl.frag");
        initCanvas();
    };

    auto update = []() -> void
    {
        while (!glfwWindowShouldClose(s_window)) {
            glfwPollEvents();
            drawCanvas();
        }
    };

    auto terminate = []() -> void
    {
        terminateCanvas();
        glfwDestroyWindow(s_window);
        glfwTerminate();
    };

    init();
    update();
    terminate();

    return 0;
}