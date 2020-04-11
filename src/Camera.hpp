#ifndef COFFEE_CAMERA_HPP
#define COFFEE_CAMERA_HPP

#include <glm/glm.hpp>

namespace coffee
{

struct Camera
{
    glm::vec3 position;
    glm::mat4 projection;
};

namespace camera
{

Camera create(const glm::ivec2 &windowSize);
glm::mat4 viewProjection(const Camera &camera);

}

}

#endif