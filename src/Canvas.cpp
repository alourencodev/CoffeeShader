#include "Canvas.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

#include "Constants.hpp"
#include "Core/File.hpp"
#include "Gui.hpp"

namespace coffee::canvas
{

constexpr char k_logTag[] = "Canvas";

Canvas create(const glm::ivec2 &windowSize)
{
    const auto clearColor = constants::k_clearColor;
    glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0f);

    Canvas::Renderables renderables = {};
    renderables.camera = camera::create(windowSize);
    renderables.mesh = mesh::create(constants::shapes::k_cube);

    Canvas::Descriptor descriptor = {};

    // TODO: Have the source on the code side
    descriptor.vertexFile.source = file::load(constants::k_defaultVertexShaderDir);
    descriptor.fragmentFile.source = file::load(constants::k_defaultFragmentShaderDir);

    if (shader::create(&renderables.shader, descriptor.vertexFile.source, descriptor.fragmentFile.source)) {
        shader::use(renderables.shader);
    } else {
        gui::log(k_logTag, "Unable to compile startup shader");
    }

    return {renderables, descriptor};
}

void draw(const Canvas::Renderables &renderables)
{
    auto mvp = camera::viewProjection(renderables.camera);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUniformMatrix4fv(renderables.shader.mvpIndex, 1, GL_FALSE, &mvp[0][0]);
    shader::updateUniforms(renderables.shader);
    glBindVertexArray(renderables.mesh.vao);
    glDrawArrays(GL_TRIANGLES, 0, renderables.mesh.vertexCount);
}

void terminate(const Canvas &canvas)
{
    shader::terminate(canvas.renderables.shader);
    mesh::clean(canvas.renderables.mesh);
}

void loadShader(Canvas *canvas, const std::string &dir, ShaderStage stage)
{
    fileWatcher::onModifiedEvent reloadShader = [canvas, stage](const std::string &dir) -> void
    {
        loadShader(canvas, dir, stage);
    };

    auto &descriptor = canvas->descriptor; 
    auto &shaderFile = stage == ShaderStage::eVertex ? descriptor.vertexFile : descriptor.fragmentFile;
    shaderFile.source = file::load(dir);

    {   // SetShader
        auto &renderables = canvas->renderables;
        Shader tempShader = renderables.shader;

        if (shader::create(&renderables.shader, descriptor.vertexFile.source, descriptor.fragmentFile.source)) {
            shader::use(renderables.shader);
        } else {
            logError("Unable to load %s", dir.c_str());
            return;
        }

        shader::terminate(tempShader);
    }

    {   // WatchFile
        fileWatcher::unwatch(shaderFile.watchHandle);
        shaderFile.watchHandle = fileWatcher::watch(dir, reloadShader);
    }
}

}