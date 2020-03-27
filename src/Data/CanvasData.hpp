#ifndef COFFEE_CANVAS_DATA_HPP
#define COFFEE_CANVAS_DATA_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace coffee
{

class CanvasData
{
public:
    GLuint shaderProgram;

    static CanvasData &get() 
    { 
        static CanvasData data;
        return data;
    };
};

}

#endif