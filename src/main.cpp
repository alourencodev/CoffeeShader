#include <GLFW/glfw3.h>

#include "Camera.hpp"
#include "Canvas.hpp"
#include "Constants.hpp"
#include "InputSystem.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "TrackballSystem.hpp"
#include "Window.hpp"

using namespace coffee; 

static GLFWwindow *s_window;
static Camera s_camera = {};
static Mesh s_mesh = {};
static Shader s_shader = {};

int main()
{
    auto init = []() -> void
    {
        window::Info windowInfo = {};
        windowInfo.title = constants::window::k_title;
        windowInfo.size = constants::window::k_size;
        windowInfo.isResizable = true;

        s_window = window::create(windowInfo);
        s_camera = camera::create(windowInfo.size);
        s_mesh = mesh::create(constants::shapes::k_cube);
        s_shader = shader::create(constants::k_defaultVertexShaderDir, constants::k_defaultFragmentShaderDir);
        shader::use(s_shader.programId);

        input::init(s_window);
        canvas::init();
        trackball::init(s_camera);
    };

    auto update = []() -> void
    {
        while (!glfwWindowShouldClose(s_window)) {
            glfwSwapBuffers(s_window);
            glfwPollEvents();
            canvas::draw(s_mesh, s_shader, camera::viewProjection(s_camera));
            trackball::update();      // TODO: Update this with a fixed framerate
        }
    };

    auto terminate = []() -> void
    {
        shader::terminate(s_shader);
        mesh::clean(s_mesh);
        glfwDestroyWindow(s_window);
        glfwTerminate();
    };

    init();
    update();
    terminate();

    return 0;
}