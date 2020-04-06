#ifndef COFFEE_INPUT_SYSTEM_HPP
#define COFFEE_INPUT_SYSTEM_HPP

#include <glm/vec2.hpp>
#include <functional>

class GLFWwindow;

namespace coffee::input
{

using eventFunction = std::function<void()>;
using eventHandle = uint32_t; //TODO: Turn this into strongly typed handler

void initInputSystem(GLFWwindow *window);
eventHandle registerMouseEvent(uint32_t button, uint32_t action, eventFunction function) noexcept;
void unregisterMouseEvent(uint32_t button, uint32_t action, eventHandle handle);
glm::vec2 mousePosition();

}

#endif