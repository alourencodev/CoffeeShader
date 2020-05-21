#include <GLFW/glfw3.h>

#include <chrono>

#include "Canvas.hpp"
#include "FileWatcher.hpp"
#include "Gui.hpp"
#include "InputSystem.hpp"
#include "TrackballSystem.hpp"
#include "Window.hpp"

using namespace coffee; 
using namespace std::chrono;

constexpr float k_framesPerSecond = 60;
constexpr int k_millisecsPerFrame = 1000 / k_framesPerSecond;
constexpr char k_title[] = "Coffee Shader";
static const glm::ivec2 k_windowSize = {1280, 720};

static GLFWwindow *s_window;
static Canvas s_canvas = {};

static void init()
{
    window::Info windowInfo = {};
    windowInfo.title = k_title;
    windowInfo.size = k_windowSize;
    windowInfo.isResizable = true;
    s_window = window::create(windowInfo);
    s_canvas = canvas::create(windowInfo.size);

    input::init(s_window);
    trackball::init(s_canvas.renderables.camera);           // After input init
    gui::init(s_window, &s_canvas);
}

static void update()
{
    glfwPollEvents();
 
    canvas::draw(s_canvas.renderables);
    gui::draw();

    if (gui::usedInput()) {
        input::discardInput();
        trackball::release();
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