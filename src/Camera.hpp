#ifndef COFFEE_CAMERA_HPP
#define COFFEE_CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace coffee
{

struct Camera
{
    glm::vec3 position;
    glm::quat rotation;
    float fieldOfView;
    float aspectRatio;
    float near;
    float far;
};

namespace camera
{

Camera create(const glm::ivec2 &windowSize);
glm::mat4 viewProjection(const Camera &camera);

}

}

#endif