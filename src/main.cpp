#include <GLFW/glfw3.h>

#include "Canvas.hpp"
#include "Constants.hpp"
#include "InputSystem.hpp"
#include "TrackballSystem.hpp"
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
        windowInfo.isResizable = true;

        s_window = initWindow(windowInfo);
        s_canvas = initCanvas(windowInfo.size);

        input::initInputSystem(s_window);
        initTrackball(s_canvas.camera);
    };

    auto update = []() -> void
    {
        while (!glfwWindowShouldClose(s_window)) {
            glfwSwapBuffers(s_window);
            glfwPollEvents();
            updateTrackball();      // TODO: Update this with a fixed framerate
            drawCanvas(s_canvas);
        }
    };

    auto terminate = []() -> void
    {
        terminateCanvas(s_canvas);
        glfwDestroyWindow(s_window);
        glfwTerminate();
    };

    init();
    update();
    terminate();

    return 0;
}