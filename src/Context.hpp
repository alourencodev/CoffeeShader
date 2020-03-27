#ifndef COFFEE_CONTEXT_HPP
#define COFFEE_CONTEXT_HPP

#include <glm/vec2.hpp>

struct GLFWwindow;

namespace coffee::context
{

class ContextData
{
public:
    GLFWwindow *window;
    glm::ivec2 windowSize;

    static ContextData &get()
    {
        static ContextData data = {};
        return data;
    }
};

void init();
bool update();
void terminate();

}

#endif