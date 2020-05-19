#ifndef COFFEE_UTILS_MATH_HPP 
#define COFFEE_UTILS_MATH_HPP

namespace coffee::utils
{

constexpr float k_pi = 3.1415926f;

constexpr float degreeToRadian(float degree)
{
    return degree * k_pi / 180.0f;
}

}

#endif