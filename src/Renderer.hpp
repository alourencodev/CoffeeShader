#ifndef COFFEE_RENDERER_HPP
#define COFFEE_RENDERER_HPP

namespace coffee
{

struct WindowInfo;

void initRenderer(const WindowInfo &windowInfo);
void draw();
void terminate();

}

#endif