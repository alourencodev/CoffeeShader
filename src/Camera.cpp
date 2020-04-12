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
    camera.rotation = glm::quat(0.0f, 0.0f, 0.0f, 1.0f);
    camera.fieldOfView = k_fieldOfView;
    camera.aspectRatio = static_cast<float>(windowSize.x) / static_cast<float>(windowSize.y);
    camera.near = k_near;
    camera.far = k_far;

    return camera;
}

glm::mat4 viewProjection(const Camera &camera)
{
    auto view = glm::lookAt(camera.rotation * camera.position, glm::vec3(0.0f), camera.rotation * constants::axis::k_up);
    auto projection = glm::perspective(camera.fieldOfView, camera.aspectRatio, camera.near, camera.far);

    return projection * view;
}

}