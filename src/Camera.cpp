#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include "Constants.hpp"

namespace coffee::camera
{

Camera create(const glm::ivec2 &windowSize)
{
    using namespace constants::camera;

    Camera camera = {};
    camera.position = k_startPosition;

    float screenRatio = static_cast<float>(windowSize.x) / static_cast<float>(windowSize.y);
    camera.projection = glm::perspective(k_fieldOfView, screenRatio, k_near, k_far);

    return camera;
}

glm::mat4 viewProjection(const Camera &camera)
{
    auto view = glm::lookAt(camera.position, glm::vec3(0.0f), constants::axis::k_up);
    return camera.projection * view;
}

}