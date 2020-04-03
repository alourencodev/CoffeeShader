#ifndef COFFEE_INPUT_SYSTEM_HPP
#define COFFEE_INPUT_SYSTEM_HPP

#include <glm/vec2.hpp>
#include <functional>

class GLFWwindow;

namespace coffee
{

using eventFunction = std::function<void()>;
using eventHandle = uint16_t; //TODO: Turn this into strongly typed handler

struct KeyEvent
{
    uint16_t key;
    uint16_t action;
    eventFunction function;
};

void initInputSystem(GLFWwindow *window);
void registerMouseEvent(KeyEvent event) noexcept;
void unregisterMouseEvent(KeyEvent event);
glm::vec2 mousePosition();

}

#endif