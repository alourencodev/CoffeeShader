#ifndef COFFEE_CANVAS_HPP
#define COFFEE_CANVAS_HPP

#include <glm/glm.hpp>

#include "Camera.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"

namespace coffee
{

struct Canvas
{
    Camera camera;
    Mesh mesh;
    Shader shader;
};

namespace canvas
{

Canvas create(const glm::ivec2 &windowSize);
void draw(const Canvas &canvas);
void terminate(const Canvas &canvas);

}

}

#endif