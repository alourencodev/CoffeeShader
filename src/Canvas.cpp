#include "Canvas.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

#include "Constants.hpp"
#include "Utils/File.hpp"

namespace coffee::canvas
{

std::pair<Canvas, CanvasDescriptor> create(const glm::ivec2 &windowSize)
{
    const auto clearColor = constants::k_clearColor;
    glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0f);

    Canvas canvas = {};
    canvas.camera = camera::create(windowSize);
    canvas.mesh = mesh::create(constants::shapes::k_cube);

    CanvasDescriptor descriptor = {};

    // TODO: Have the source on the code side
    descriptor.vertexFile.source = file::load(constants::k_defaultVertexShaderDir);
    descriptor.fragmentFile.source = file::load(constants::k_defaultFragmentShaderDir);

    canvas.shader = shader::create(descriptor.vertexFile.source, descriptor.fragmentFile.source);
    shader::use(canvas.shader);

    return {canvas, descriptor};
}

void draw(const Canvas &canvas)
{
    auto mvp = camera::viewProjection(canvas.camera);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUniformMatrix4fv(canvas.shader.mvpIndex, 1, GL_FALSE, &mvp[0][0]);
    shader::updateUniforms(canvas.shader);
    glBindVertexArray(canvas.mesh.vao);
    glDrawArrays(GL_TRIANGLES, 0, canvas.mesh.vertexCount);
}

void terminate(const Canvas &canvas)
{
    shader::terminate(canvas.shader);
    mesh::clean(canvas.mesh);
}

void loadShader(Canvas *canvas, CanvasDescriptor *descriptor, const std::string &dir, ShaderStage stage)
{
    fileWatcher::onModifiedEvent reloadShader = [canvas, descriptor, stage](const std::string &dir) -> void
    {
        loadShader(canvas, descriptor, dir, stage);
    };

    auto &shaderFile = stage == ShaderStage::eVertex ? descriptor->vertexFile : descriptor->fragmentFile;
    shaderFile.source = file::load(dir);

    {   // SetShader
        Shader tempShader = canvas->shader;
        canvas->shader = shader::create(descriptor->vertexFile.source, descriptor->fragmentFile.source);
        shader::use(canvas->shader);
        shader::terminate(tempShader);
    }

    {   // WatchFile
        fileWatcher::unwatch(shaderFile.watchHandle);
        shaderFile.watchHandle = fileWatcher::watch(dir, reloadShader);
    }
}

}