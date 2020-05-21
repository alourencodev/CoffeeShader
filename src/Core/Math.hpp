#ifndef COFFEE_UTILS_MATH_HPP 
#define COFFEE_UTILS_MATH_HPP

#include <glm/vec3.hpp>

namespace coffee::math
{

constexpr float k_pi = 3.1415926f;

namespace axis
{
static const glm::vec3 k_up = {0.0f, 1.0f, 0.0f};
static const glm::vec3 k_right {1.0f, 0.0f, 0.0f};
}

constexpr float degreeToRadian(float degree)
{
    return degree * k_pi / 180.0f;
}

}

#endif