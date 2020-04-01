#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include "Utils/Math.hpp"
#include "Window.hpp"

namespace coffee
{

static const glm::vec3 k_position = {4.0f, 3.0f, 3.0f};
static const glm::vec3 k_up = {0.0f, 1.0f, 0.0f};

constexpr float k_fieldOfView = utils::math::degreeToRadian(45.0f);
constexpr float k_near = 0.1f;
constexpr float k_far = 100.0f;

Camera initCamera(const glm::ivec2 &windowSize)
{
    Camera camera = {};
    camera.view = glm::lookAt(k_position, glm::vec3(0.0f), k_up);

    float screenRatio = static_cast<float>(windowSize.x) / static_cast<float>(windowSize.y);
    camera.projection = glm::perspective(k_fieldOfView, screenRatio, k_near, k_far);

    return camera;
}

}