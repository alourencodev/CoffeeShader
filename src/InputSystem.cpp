#include "InputSystem.hpp"

#include <iostream>

#include <GLFW/glfw3.h>
#include <vector>
#include <memory>
#include <utility>

#include "Canvas.hpp"
#include "Utils/Containers.hpp"
#include "Utils/Log.hpp"
#include "Utils/Matrix.hpp"

namespace coffee::input
{

constexpr char k_logTag[] = "InputSystem";

struct Event
{
    EventHandle handle;
    eventFunction function;

    bool operator == (const Event &other) const { return handle == other.handle; }
};

using MouseEventTable = matrix<std::vector<Event>, GLFW_MOUSE_BUTTON_LAST, GLFW_REPEAT>;    // GLFW_REPEATE is the last action integer

static glm::ivec2 s_mousePosition = {};
static std::unique_ptr<MouseEventTable> s_mouseEventTable;

void init(GLFWwindow *window)
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

EventHandle registerMouseEvent(uint32_t button, uint32_t action, eventFunction function) noexcept
{
    static uint16_t s_currentEventHandleCounter = 0;

    const auto handle = EventHandle(s_currentEventHandleCounter);
    Event event = {handle, function};
    s_mouseEventTable->at(button, action).emplace_back(std::move(event));
    s_currentEventHandleCounter++;

    return handle;
}

void unregisterMouseEvent(uint32_t button, uint32_t action, EventHandle handle)
{
    auto &eventArray = s_mouseEventTable->at(button, action);
    Event findEvent = {handle, []() -> void {}};
    const auto &it = std::find(eventArray.begin(), eventArray.end(), findEvent);
    if (it != eventArray.end()) {
        utils::unorderedRemove(eventArray, it);
        return;
    }

    logWarning(k_logTag, "Can't unregister event %d from action %d and button %d", handle, action, button);
}

const glm::vec2 mousePosition()
{
    return s_mousePosition;
}

}