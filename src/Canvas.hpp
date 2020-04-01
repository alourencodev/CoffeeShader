#ifndef COFFEE_CANVAS_HPP
#define COFFEE_CANVAS_HPP

#include "Camera.hpp"

namespace coffee
{

struct Canvas
{
    Camera camera = {};
};

void initCanvas();
void drawCanvas();
void terminateCanvas();

}

#endif