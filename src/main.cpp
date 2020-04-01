#include <GLFW/glfw3.h>

#include "Canvas.hpp"
#include "Constants.hpp"
#include "ShaderSystem.hpp"
#include "Window.hpp"

using namespace coffee;

static GLFWwindow *s_window;
static Canvas s_canvas = {};

int main()
{
    auto init = []() -> void
    {
        WindowInfo windowInfo = {};
        windowInfo.title = constants::window::k_title;
        windowInfo.size = constants::window::k_size;

        s_window = initWindow(windowInfo);

        shaderSystem::setShader("shaders/default.glsl.vert", "shaders/default.glsl.frag");
        s_canvas = initCanvas(windowInfo.size);
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