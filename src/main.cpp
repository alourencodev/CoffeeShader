#include "Context.hpp"
#include "ShaderSystem.hpp"
#include "Renderer.hpp"

using namespace coffee;

int main()
{
    context::init();
    shaderSystem::setShader("shaders/default.vert.glsl", "shaders/default.frag.glsl");
    renderer::init();

    while (context::update()) {
        renderer::draw();
    }

    renderer::terminate();
    context::terminate();

    return 0;
}