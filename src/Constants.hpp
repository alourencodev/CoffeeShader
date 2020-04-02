#ifndef COFFEE_CONSTANTS_HPP
#define COFFEE_CONSTANTS_HPP

#include <glm/glm.hpp>
#include <string>

#include "Utils/Math.hpp"

namespace coffee::constants
{

namespace window
{

constexpr char k_title[] = "Coffee Shader";
static const glm::ivec2 k_size = {1920, 1080};

}

namespace canvas
{

static const glm::vec3 k_clearColor = {0.2f, 0.2f, 0.2f};
constexpr char k_defaultVertexShaderDir[] = "shaders/default.glsl.vert";
constexpr char k_defaultFragmentShaderDir[] = "shaders/default.glsl.frag";

}

namespace camera
{

static const glm::vec3 k_position = {4.0f, 3.0f, 3.0f};
static const glm::vec3 k_up = {0.0f, 1.0f, 0.0f};

constexpr float k_fieldOfView = utils::math::degreeToRadian(45.0f);
constexpr float k_near = 0.1f;
constexpr float k_far = 100.0f;

}

namespace shader
{

constexpr char k_mvpUniform[] = "uMVP";

}

} 

#endif