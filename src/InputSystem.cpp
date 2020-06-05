#include "InputSystem.hpp"

#include <array>
#include <GLFW/glfw3.h>
#include <memory>
#include <utility>
#include <vector>

#include "Core/Containers.hpp"
#include "Core/Log.hpp"

namespace coffee::input
{

constexpr char k_logTag[] = "InputSystem";

struct ButtonActionPair
{
    int button;
    int action;
};

struct Event
{
    EventHandle handle;
    eventFunction function;

    bool operator == (const Event &other) const { return handle == other.handle; }
};

using MouseEventTable = matrix<std::vector<Event>, GLFW_MOUSE_BUTTON_LAST, GLFW_REPEAT>;    // GLFW_REPEATE is the last action integer

static glm::ivec2 s_mousePosition = {};
static MouseEventTable s_mouseEventTable;
static std::array<ButtonActionPair, 8> s_mouseEventQueue;
static uint8_t s_lastMouseEventIndex = 0;

void init(GLFWwindow *window)
{
    glfwSetCursorPosCallback(window, [] (GLFWwindow *, double posX, double posY) -> void
    {
        s_mousePosition = {static_cast<int>(posX), static_cast<int>(posY)};
    });

    glfwSetMouseButtonCallback(window, [](GLFWwindow *, int button, int action, int) -> void
    {
        s_mouseEventQueue[s_lastMouseEventIndex++] = {button, action};
    });
}

EventHandle registerMouseEvent(uint32_t button, uint32_t action, eventFunction function) noexcept
{
    static uint16_t s_currentEventHandleCounter = 0;

    const auto handle = EventHandle(s_currentEventHandleCounter);
    Event event = {handle, function};
    s_mouseEventTable.at(button, action).emplace_back(std::move(event));
    s_currentEventHandleCounter++;

    return handle;
}

void unregisterMouseEvent(uint32_t button, uint32_t action, EventHandle handle)
{
    auto &eventArray = s_mouseEventTable.at(button, action);
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

void poll()
{
    for (int i = 0; i < s_lastMouseEventIndex; i++) {
        auto input = s_mouseEventQueue[i];
        for (auto &event : s_mouseEventTable.at(input.button, input.action)) {
            event.function();
        }
    }

    s_lastMouseEventIndex = 0;
}

void discardInput()
{
    s_lastMouseEventIndex = 0;
}

}