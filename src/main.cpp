#include "Context.hpp"
#include "ShaderSystem.hpp"
#include "Renderer.hpp"

using namespace coffee;

int main()
{
    context::init();
    shaderSystem::setShader("shaders/default.glsl.vert", "shaders/default.glsl.frag");
    renderer::init();

    while (context::update()) {
        renderer::draw();
    }

    renderer::terminate();
    context::terminate();

    return 0;
}