#ifndef COFFEE_GUI_HPP
#define COFFEE_GUI_HPP

class GLFWwindow;

namespace coffee
{

struct Canvas;
namespace gui
{

void init(GLFWwindow *window, Canvas *canvas);
void draw();
void terminate();

}

}

#endif