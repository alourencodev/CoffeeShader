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

// FIXME: This initialization is horrible. I need to get a better solution
static CanvasDescriptor s_canvasDescriptor= {{"", fileWatcher::WatchHandle(0)},{"", fileWatcher::WatchHandle(0)}};

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
    gui::init(s_window, &s_canvas, &s_canvasDescriptor);

    // TRASH: For test purposes
    s_canvasDescriptor.vertexFile.dir = constants::k_defaultVertexShaderDir;
    s_canvasDescriptor.fragmentFile.dir = constants::k_defaultFragmentShaderDir;
    s_canvasDescriptor.vertexFile.watchHandle = fileWatcher::watch(constants::k_defaultVertexShaderDir, recreateShader);
    s_canvasDescriptor.fragmentFile.watchHandle = fileWatcher::watch(constants::k_defaultFragmentShaderDir, recreateShader);
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