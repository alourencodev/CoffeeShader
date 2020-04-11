#include "TrackballSystem.hpp"

// FIXME: Get an alternative for this anoying thing!!
#define GLM_ENABLE_EXPERIMENTAL

#include <GLFW/glfw3.h>
#include <functional>
#include <glm/gtx/rotate_vector.hpp>

#include "Camera.hpp"
#include "Constants.hpp"
#include "InputSystem.hpp"

namespace coffee
{

constexpr float k_rotationSpeed = 0.01f; // TODO: Calibrate

static std::function<void()> s_updateFunction = []() -> void {};
static glm::ivec2 s_lastMousePosition;
static Camera *s_registeredCamera = nullptr;

void updateCamera()
{
    glm::ivec2 mousePosition = input::mousePosition();
    auto deltaPosition = mousePosition - s_lastMousePosition;
    s_lastMousePosition = mousePosition;

    float yaw = -deltaPosition.x * k_rotationSpeed;
    float pitch = -deltaPosition.y * k_rotationSpeed;

    // FIXME: Avoid Gimbal lock
    s_registeredCamera->position = glm::rotate(s_registeredCamera->position, pitch, constants::axis::k_right);
    s_registeredCamera->position = glm::rotate(s_registeredCamera->position, yaw, constants::axis::k_up);
}

void initTrackball(Camera &camera)
{
    // TODO: Check a better solution for this
    s_registeredCamera = &camera;

    auto onPress = []() -> void
    {
        s_updateFunction = updateCamera;
        s_lastMousePosition = input::mousePosition();
    };

    auto onRelease = []() -> void
    {
        s_updateFunction = []() -> void {};
    };

    input::registerMouseEvent(GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, onPress);
    input::registerMouseEvent(GLFW_MOUSE_BUTTON_LEFT, GLFW_RELEASE, onRelease);
}

void updateTrackball()
{
    // CHECK: if it's better to call an empty lambda or make a null check?
    s_updateFunction();
}

}