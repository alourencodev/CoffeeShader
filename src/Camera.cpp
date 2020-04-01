#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include "Constants.hpp"

namespace coffee
{

Camera initCamera(const glm::ivec2 &windowSize)
{
    using namespace constants::camera;

    Camera camera = {};
    camera.view = glm::lookAt(k_position, glm::vec3(0.0f), k_up);

    float screenRatio = static_cast<float>(windowSize.x) / static_cast<float>(windowSize.y);
    camera.projection = glm::perspective(k_fieldOfView, screenRatio, k_near, k_far);

    return camera;
}

}