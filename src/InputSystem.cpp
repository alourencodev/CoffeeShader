#include "InputSystem.hpp"

#include <iostream>

#include <GLFW/glfw3.h>
#include <vector>
#include <memory>
#include <utility>

#include "Canvas.hpp"
#include "Utils/Containers.hpp"
#include "Utils/Matrix.hpp"

namespace coffee::input
{

struct Event
{
    eventHandle handle;
    eventFunction function;

    bool operator == (const Event &other) const { return handle == other.handle; }
};

using MouseEventTable = matrix<std::vector<Event>, GLFW_MOUSE_BUTTON_LAST, GLFW_REPEAT>;

static glm::ivec2 s_mousePosition = {};
static std::unique_ptr<MouseEventTable> s_mouseEventTable;
static eventHandle s_currentEventHandle = 0;

void initInputSystem(GLFWwindow *window)
{
    s_mouseEventTable = std::make_unique<MouseEventTable>();

    glfwSetCursorPosCallback(window, [] (GLFWwindow *, double posX, double posY) -> void
    {
        s_mousePosition = {static_cast<int>(posX), static_cast<int>(posY)};
    });

    glfwSetMouseButtonCallback(window, [](GLFWwindow *, int button, int action, int) -> void
    {
        for (auto &event : s_mouseEventTable->at(button, action)) {
            event.function();
        }
    });

}

eventHandle registerMouseEvent(uint32_t button, uint32_t action, eventFunction function) noexcept
{
    Event event = {s_currentEventHandle, function};
    s_mouseEventTable->at(button, action).emplace_back(std::move(event));
    return s_currentEventHandle++;
}

void unregisterMouseEvent(uint32_t button, uint32_t action, eventHandle handle)
{
    auto &eventArray = s_mouseEventTable->at(button, action);
    Event findEvent = {handle, []() -> void {}};
    const auto &it = std::find(eventArray.begin(), eventArray.end(), findEvent);
    if (it != eventArray.end()) {
        utils::unorderedRemove(eventArray, it);
        return;
    }

    // TODO: WARN
}

glm::vec2 mousePosition()
{
    return s_mousePosition;
}

}