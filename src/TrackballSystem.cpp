#include "TrackballSystem.hpp"

// FIXME: Get an alternative for this anoying thing!!
#define GLM_ENABLE_EXPERIMENTAL

#include <GLFW/glfw3.h>
#include <functional>
#include <glm/gtx/rotate_vector.hpp>

#include "Camera.hpp"
#include "Constants.hpp"
#include "InputSystem.hpp"

namespace coffee::trackball
{

constexpr float k_rotationSpeed = 0.01f; // TODO: Calibrate

static std::function<void()> s_updateFunction = []() -> void {};
static glm::ivec2 s_lastMousePosition;

void init(Camera &camera)
{
    std::function<void()> updateCameraRotation = [&camera]() -> void
    {
        glm::ivec2 mousePosition = input::mousePosition();
        auto deltaPosition = mousePosition - s_lastMousePosition;
        s_lastMousePosition = mousePosition;

        float yaw = -deltaPosition.x * k_rotationSpeed;
        float pitch = -deltaPosition.y * k_rotationSpeed;

        // FIXME: Avoid Gimbal lock
        camera.position = glm::rotate(camera.position, pitch, constants::axis::k_right);
        camera.position = glm::rotate(camera.position, yaw, constants::axis::k_up);
    };

    auto onPress = [updateCameraRotation]() -> void
    {
        s_updateFunction = updateCameraRotation;
        s_lastMousePosition = input::mousePosition();
    };

    auto onRelease = []() -> void
    {
        s_updateFunction = []() -> void {};
    };

    input::registerMouseEvent(GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, onPress);
    input::registerMouseEvent(GLFW_MOUSE_BUTTON_LEFT, GLFW_RELEASE, onRelease);
}

void update()
{
    // CHECK: if it's better to call an empty lambda or make a null check?
    s_updateFunction();
}

}