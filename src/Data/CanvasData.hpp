#ifndef COFFEE_CANVAS_DATA_HPP
#define COFFEE_CANVAS_DATA_HPP

#include <glad/glad.h>

namespace coffee
{

class CanvasData
{
public:
    GLuint shaderProgram;

    static CanvasData &get() { return _instance; };
    
private:
    static CanvasData _instance;
}

}

#endif