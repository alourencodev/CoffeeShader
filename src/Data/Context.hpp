#ifndef COFFEE_CONTEXT_HPP
#define COFFEE_CONTEXT_HPP

#include <glm/vec2.hpp>

struct GLFWwindow;

namespace coffee
{

class Context
{
public:
    GLFWwindow *window;
    glm::ivec2 windowSize;

    static Context &get()
    {
        static Context data = {};
        return data;
    }
};

}

#endif