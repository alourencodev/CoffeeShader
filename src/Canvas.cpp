#include "Canvas.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

#include "Camera.hpp"
#include "Window.hpp"

namespace coffee
{

void initRenderer(const WindowInfo &windowInfo)
{

}

Canvas initCanvas(const glm::ivec2 &windowSize)
{
    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);

    Canvas canvas = {};
    canvas.camera = initCamera(windowSize);

    return canvas;
}

void drawCanvas()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // glUseProgram(Canvas::get().shaderProgram);
    // glUniformMatrix4fv(glad_glGetUniformLocation(Canvas::get().shaderProgram, "mvp"), 1, GL_FALSE, &s_mvp[0][0]);
    // glBindVertexArray(s_cubeVao);
    // glDrawArrays(GL_TRIANGLES, 0, shapes::k_cube.size() / 3);
    // glBindVertexArray(0);
}

void terminateCanvas()
{
    // glBindVertexArray(s_cubeVao);
    // glDisableVertexAttribArray(k_shaderPositionIndex);
    // glDeleteBuffers(1, &s_cubeVbo);
    // glBindVertexArray(0);
    // glDeleteVertexArrays(1, &s_cubeVao);
}

}