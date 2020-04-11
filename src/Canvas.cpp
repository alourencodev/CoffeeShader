#include "Canvas.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

#include "Constants.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"

namespace coffee::canvas
{

void init()
{
    using namespace constants;
    glClearColor(k_clearColor.r, k_clearColor.g, k_clearColor.b, 1.0f);
}

void draw(const Mesh &mesh, const Shader &shader, const glm::mat4 &mvp)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUniformMatrix4fv(shader.mvpIndex, 1, GL_FALSE, &mvp[0][0]);
    glBindVertexArray(mesh.vao);
    glDrawArrays(GL_TRIANGLES, 0, mesh.vertexCount);
    glBindVertexArray(0);   // CHECK: if this is needed?
}

}