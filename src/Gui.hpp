#ifndef COFFEE_GUI_HPP
#define COFFEE_GUI_HPP

class GLFWwindow;

namespace coffee
{

struct Canvas;
struct CanvasDescriptor;
namespace gui
{

void init(GLFWwindow *window, Canvas *canvas, CanvasDescriptor *descriptor);
void draw();
void terminate();
bool usedInput();

}

}

#endif