#include "InputSystem.hpp"

#include <iostream>

#include <GLFW/glfw3.h>
#include <array>
#include <vector>

#include "Canvas.hpp"
#include "Utils/Containers.hpp"

namespace coffee
{

static glm::ivec2 s_mousePosition = {};

void initInputSystem(GLFWwindow *window)
{
    glfwSetCursorPosCallback(window, [] (GLFWwindow *window, double posX, double posY) -> void
    {
        s_mousePosition = {static_cast<int>(posX), static_cast<int>(posY)};
    });
}

void registerMouseEvent(KeyEvent event) noexcept
{
    // TODO
}

void unregisterMouseEvent(KeyEvent event)
{
    // TODO
}

glm::vec2 mousePosition()
{
    return s_mousePosition;
}

}