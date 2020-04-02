#ifndef COFFEE_CANVAS_HPP
#define COFFEE_CANVAS_HPP

#include "Camera.hpp"
#include "MeshLoader.hpp"
#include "ShaderLoader.hpp"

namespace coffee
{

struct Canvas
{
    Camera camera = {};
    Mesh mesh = {};
    Shader shader = {};
};

Canvas initCanvas(const glm::ivec2 &windowSize);
void drawCanvas(const Canvas &canvas);
void terminateCanvas(const Canvas &canvas);

}

#endif