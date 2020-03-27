#include "ContextSystem.hpp"
#include "ShaderSystem.hpp"
#include "Renderer.hpp"

using namespace coffee;

int main()
{
    system::context::init();
    shaderSystem::setShader("shaders/default.glsl.vert", "shaders/default.glsl.frag");
    renderer::init();

    while (system::context::update()) {
        renderer::draw();
    }

    renderer::terminate();
    system::context::terminate();

    return 0;
}