#ifndef COFFEE_CANVAS_HPP
#define COFFEE_CANVAS_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace coffee
{

class Canvas
{
public:
    GLuint shaderProgram;

    static Canvas &get() 
    { 
        static Canvas data;
        return data;
    };
};

}

#endif