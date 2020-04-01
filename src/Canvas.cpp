#include "Canvas.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

#include "Camera.hpp"
#include "Constants.hpp"
#include "ShaderLoader.hpp"
#include "Window.hpp"

namespace coffee
{

Canvas initCanvas(const glm::ivec2 &windowSize)
{
    using namespace constants::canvas;

    glClearColor(k_clearColor.r, k_clearColor.g, k_clearColor.b, 1.0f);

    Canvas canvas = {};
    canvas.camera = initCamera(windowSize);
    canvas.shaderProgram = loadShader(k_defaultVertexShaderDir, k_defaultFragmentShaderDir);

    glUseProgram(canvas.shaderProgram);

    return canvas;
}

void drawCanvas(const Canvas &canvas)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // glUniformMatrix4fv(glad_glGetUniformLocation(Canvas::get().shaderProgram, "mvp"), 1, GL_FALSE, &s_mvp[0][0]);
    // glBindVertexArray(s_cubeVao);
    // glDrawArrays(GL_TRIANGLES, 0, shapes::k_cube.size() / 3);
    // glBindVertexArray(0);
}

void terminateCanvas(const Canvas &canvas)
{
    glDeleteProgram(canvas.shaderProgram);
    // glBindVertexArray(s_cubeVao);
    // glDisableVertexAttribArray(k_shaderPositionIndex);
    // glDeleteBuffers(1, &s_cubeVbo);
    // glBindVertexArray(0);
    // glDeleteVertexArrays(1, &s_cubeVao);
}

}