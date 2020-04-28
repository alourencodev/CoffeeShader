#ifndef COFFEE_GUI_HPP
#define COFFEE_GUI_HPP

class GLFWwindow;

namespace coffee::gui
{

void init(GLFWwindow *window);
void draw();
void terminate();

}

#endif