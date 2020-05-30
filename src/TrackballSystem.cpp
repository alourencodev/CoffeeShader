#include "TrackballSystem.hpp"

#include <GLFW/glfw3.h>
#include <functional>

#include "Camera.hpp"
#include "Core/Assert.hpp"
#include "Core/Math.hpp"
#include "InputSystem.hpp"

namespace coffee::trackball
{

constexpr float k_rotationSpeed = 0.005f;

static glm::ivec2 s_lastMousePosition;
static bool s_isDragging = false;
static Camera *s_camera;

void init(Camera *camera)
{
    ASSERT(camera != nullptr);
    s_camera = camera;

    auto onPress = []() -> void
    {
        s_isDragging = true;
        s_lastMousePosition = input::mousePosition();
    };

    input::registerMouseEvent(GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, onPress);
    input::registerMouseEvent(GLFW_MOUSE_BUTTON_LEFT, GLFW_RELEASE, release);
}

void release()
{
    s_isDragging = false;
}

void update()
{
    if (s_isDragging)
    {
        glm::ivec2 mousePosition = input::mousePosition();
        auto deltaPosition = mousePosition - s_lastMousePosition;
        s_lastMousePosition = mousePosition;

        float yaw = -deltaPosition.x * k_rotationSpeed;
        float pitch = -deltaPosition.y * k_rotationSpeed;

        auto rotationQuat = glm::angleAxis(pitch, math::axis::k_right) * glm::angleAxis(yaw, math::axis::k_up);
        s_camera->rotation = s_camera->rotation * rotationQuat; 
    }
}

}
