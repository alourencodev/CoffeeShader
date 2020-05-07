#include "Canvas.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

#include "Constants.hpp"

namespace coffee::canvas
{

Canvas create(const glm::ivec2 &windowSize)
{
    const auto clearColor = constants::k_clearColor;
    glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0f);

    Canvas canvas = {};
    canvas.camera = camera::create(windowSize);
    canvas.mesh = mesh::create(constants::shapes::k_cube);
    canvas.shader = shader::create(constants::k_defaultVertexShaderDir, constants::k_defaultFragmentShaderDir);
    shader::use(canvas.shader);

    return canvas;
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

inline void loadShader(Canvas *canvas, const std::string &vertexDir, const std::string &fragmentDir)
{
    Shader tempShader = canvas->shader;
    canvas->shader = shader::create(vertexDir, fragmentDir);
    shader::use(canvas->shader);
    shader::terminate(tempShader);
}

void setCanvasShader(Canvas *canvas, CanvasDescriptor *descriptor, const std::string &vertexDir, const std::string &fragmentDir)
{
    std::function<void()> reloadShader = [canvas, descriptor]() -> void
    {
        loadShader(canvas, descriptor->vertexFile.dir, descriptor->fragmentFile.dir);
    };

    loadShader(canvas, vertexDir, fragmentDir);

    descriptor->vertexFile.dir = vertexDir;
    descriptor->fragmentFile.dir = fragmentDir;

    // TODO: Get a way to avoid redundant unwatches
    fileWatcher::unwatch(descriptor->vertexFile.watchHandle);
    fileWatcher::unwatch(descriptor->fragmentFile.watchHandle);

    descriptor->vertexFile.watchHandle = fileWatcher::watch(vertexDir, reloadShader);
    descriptor->fragmentFile.watchHandle = fileWatcher::watch(fragmentDir, reloadShader);
}

}