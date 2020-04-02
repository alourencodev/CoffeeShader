#include "Canvas.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

#include "Camera.hpp"
#include "Constants.hpp"
#include "Data/Shapes.hpp"
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
    canvas.mesh = createMesh(shapes::k_cube);

    glUseProgram(canvas.shaderProgram);

    return canvas;
}

void drawCanvas(const Canvas &canvas)
{
    glad_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glad_glBindVertexArray(canvas.mesh.vao);
    glad_glDrawArrays(GL_TRIANGLES, 0, canvas.mesh.vertexCount);
    glad_glBindVertexArray(0);   // CHECK: Is this needed?
}

void terminateCanvas(const Canvas &canvas)
{
    glDeleteProgram(canvas.shaderProgram);
    cleanMesh(canvas.mesh);
}

}