#ifndef COFFEE_CAMERA_HPP
#define COFFEE_CAMERA_HPP

#include <glm/glm.hpp>

namespace coffee
{

struct Camera
{
    glm::mat4 view;
    glm::mat4 projection;
};

Camera initCamera(const glm::ivec2 &windowSize);

}

#endif