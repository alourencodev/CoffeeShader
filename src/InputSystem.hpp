#ifndef COFFEE_INPUT_SYSTEM_HPP
#define COFFEE_INPUT_SYSTEM_HPP

#include <glm/vec2.hpp>
#include <functional>

#include "Utils/Handle.hpp"

class GLFWwindow;

namespace coffee::input
{

DEFINE_HANDLE(EventHandle);

using eventFunction = std::function<void()>;

void init(GLFWwindow *window);
EventHandle registerMouseEvent(uint32_t button, uint32_t action, eventFunction function) noexcept;
void unregisterMouseEvent(uint32_t button, uint32_t action, EventHandle handle);
glm::vec2 mousePosition();

}

#endif