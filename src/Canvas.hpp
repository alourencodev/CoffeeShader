#ifndef COFFEE_CANVAS_HPP
#define COFFEE_CANVAS_HPP

#include "Camera.hpp"

namespace coffee
{

struct Canvas
{
    Camera camera = {};
};

Canvas initCanvas(const glm::ivec2 &windowSize);
void drawCanvas();
void terminateCanvas();

}

#endif