#ifndef COFFEE_CANVAS_HPP
#define COFFEE_CANVAS_HPP

#include <glm/glm.hpp>

namespace coffee
{

struct Mesh;
struct Shader;

namespace canvas
{

void init();
void draw(const Mesh &mesh, const Shader &shader, const glm::mat4 &mvp);

}

}

#endif