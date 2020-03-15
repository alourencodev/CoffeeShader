#include "Context.hpp"
#include "ShaderSystem.hpp"

using namespace coffee;

int main()
{
    context::init();
    shaderSystem::setShader("default.vert.glsl", "default.frag.glsl");

    while (context::update()) {
    }

    context::terminate();

    return 0;
}