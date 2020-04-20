#include <GLFW/glfw3.h>

#include <chrono>

#include "Canvas.hpp"
#include "Constants.hpp"
#include "FileWatcher.hpp"
#include "InputSystem.hpp"
#include "TrackballSystem.hpp"
#include "Window.hpp"

using namespace coffee; 
using namespace std::chrono;

constexpr int k_millisecsPerFrame = 1000 / constants::k_framesPerSecond;

static GLFWwindow *s_window;
static Canvas s_canvas = {};

static void init()
{
    std::function<void()> recreateShader = []() -> void
    {
        Shader tempShader = s_canvas.shader;
        s_canvas.shader = shader::create(constants::k_defaultVertexShaderDir, constants::k_defaultFragmentShaderDir);
        shader::use(s_canvas.shader);
        shader::terminate(tempShader);
    };

    window::Info windowInfo = {};
    windowInfo.title = constants::window::k_title;
    windowInfo.size = constants::window::k_size;
    windowInfo.isResizable = true;
    s_window = window::create(windowInfo);
    s_canvas = canvas::create(windowInfo.size);

    input::init(s_window);
    trackball::init(s_canvas.camera);           // After input init

    // TODO: Move this to another place
    fileWatcher::watch(constants::k_defaultVertexShaderDir, recreateShader);
    fileWatcher::watch(constants::k_defaultFragmentShaderDir, recreateShader);
}

static void update()
{
    glfwSwapBuffers(s_window);
    glfwPollEvents();
    canvas::draw(s_canvas);
}

static void fixedUpdate()
{
    trackball::update();
    fileWatcher::poll();
}

static void terminate()
{
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