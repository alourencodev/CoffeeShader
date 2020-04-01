#ifndef COFFEE_WINDOW_HPP
#define COFFEE_WINDOW_HPP

#include <glm/vec2.hpp>
#include <string>

struct GLFWwindow;

namespace coffee
{

struct WindowInfo
{
    std::string title = "";
    glm::ivec2 size = {800, 600};
    bool isResizable = false;
};

GLFWwindow *initWindow(const WindowInfo &info);

}

#endif