#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include "Core/Math.hpp"

namespace coffee::camera
{

static const glm::vec3 k_startPosition = {0.0f, 0.0f, 6.0f};
constexpr float k_fieldOfView = math::degreeToRadian(45.0f);
constexpr float k_near = 0.1f;
constexpr float k_far = 100.0f;

Camera create(const glm::ivec2 &windowSize)
{
    Camera camera = {};
    camera.position = k_startPosition;
    camera.rotation = glm::quat(0.0f, 0.0f, 0.0f, 1.0f);
    camera.fieldOfView = k_fieldOfView;
    camera.aspectRatio = static_cast<float>(windowSize.x) / static_cast<float>(windowSize.y);
    camera.near = k_near;
    camera.far = k_far;

    return camera;
}

void onWindowResize(Camera *camera, int width, int height)
{
    camera->aspectRatio = static_cast<float>(width) / static_cast<float>(height);
}

glm::mat4 viewProjection(const Camera &camera)
{
    auto view = glm::lookAt(camera.rotation * camera.position, glm::vec3(0.0f), camera.rotation * math::axis::k_up);
    auto projection = glm::perspective(camera.fieldOfView, camera.aspectRatio, camera.near, camera.far);

    return projection * view;
}

}