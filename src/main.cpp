#include <GLFW/glfw3.h>

#include <chrono>

#include "Canvas.hpp"
#include "Constants.hpp"
#include "FileWatcher.hpp"
#include "Gui.hpp"
#include "InputSystem.hpp"
#include "TrackballSystem.hpp"
#include "Window.hpp"

using namespace coffee; 
using namespace std::chrono;

constexpr int k_millisecsPerFrame = 1000 / constants::k_framesPerSecond;

static GLFWwindow *s_window;
static Canvas s_canvas = {}; 
static CanvasDescriptor s_canvasDescriptor = {};

static void init()
{
    window::Info windowInfo = {};
    windowInfo.title = constants::window::k_title;
    windowInfo.size = constants::window::k_size;
    windowInfo.isResizable = true;
    s_window = window::create(windowInfo);

    // TODO: Have a better structure for this
    auto pair = canvas::create(windowInfo.size);
    s_canvas = pair.first;
    s_canvasDescriptor = pair.second;

    input::init(s_window);
    trackball::init(s_canvas.camera);           // After input init
    gui::init(s_window, &s_canvas, &s_canvasDescriptor);
}

static void update()
{
    glfwPollEvents();
 
    canvas::draw(s_canvas);
    gui::draw();

    if (gui::usedInput()) {
        input::discardInput();
    } else {
        input::poll();
    }

    glfwSwapBuffers(s_window);
}

static void fixedUpdate()
{
    trackball::update();
    fileWatcher::poll();
}

static void terminate()
{
    gui::terminate();
    canvas::terminate(s_canvas);
    glfwDestroyWindow(s_window);
    glfwTerminate();
}

int main()
{
    init();

    auto lastTime = steady_clock::now();
    while (!glfwWindowShouldClose(s_window)) {
        update();

        auto now = steady_clock::now();
        if (duration_cast<milliseconds>(now - lastTime).count() > k_millisecsPerFrame) {
            fixedUpdate();
            lastTime = now;
        }        
    }
    
    terminate();

    return 0;
}