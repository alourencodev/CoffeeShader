#include "Canvas.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

#include "Camera.hpp"
#include "Constants.hpp"
#include "Data/Shapes.hpp"
#include "Window.hpp"

namespace coffee
{

Canvas initCanvas(const glm::ivec2 &windowSize)
{
    using namespace constants::canvas;

    glClearColor(k_clearColor.r, k_clearColor.g, k_clearColor.b, 1.0f);

    Canvas canvas = {};
    canvas.camera = initCamera(windowSize);
    canvas.shader = loadShader(k_defaultVertexShaderDir, k_defaultFragmentShaderDir);
    canvas.mesh = createMesh(shapes::k_cube);

    glUseProgram(canvas.shader.programId);

    return canvas;
}

void drawCanvas(const Canvas &canvas)
{
    // CHECK: If this can only be set when needed
    auto view = glm::lookAt(canvas.camera.position, glm::vec3(0.0f), constants::axis::k_up);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glm::mat4 mvp = canvas.camera.projection * view;
    glUniformMatrix4fv(canvas.shader.mvpIndex, 1, GL_FALSE, &mvp[0][0]);
    glBindVertexArray(canvas.mesh.vao);
    glDrawArrays(GL_TRIANGLES, 0, canvas.mesh.vertexCount);
    glBindVertexArray(0);   // CHECK: if this is needed?
}

void terminateCanvas(const Canvas &canvas)
{
    glDeleteProgram(canvas.shader.programId);
    cleanMesh(canvas.mesh);
}

}