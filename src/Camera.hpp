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

Camera initCamera(const glm::ivec2 &windowSize);

}

#endif