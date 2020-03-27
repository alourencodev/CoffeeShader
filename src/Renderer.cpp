#include "Renderer.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

#include "Data/CanvasData.hpp"
#include "Data/Shapes.hpp"
#

namespace coffee::renderer
{

static const GLuint k_shaderPositionIndex = 0; 

static GLuint s_cubeVao;
static GLuint s_cubeVbo;

void init()
{

    glGenVertexArrays(1, &s_cubeVao);
    glBindVertexArray(s_cubeVao);
    {
        glGenBuffers(1, &s_cubeVbo);
        glBindBuffer(GL_ARRAY_BUFFER, s_cubeVbo);
        glBufferData(GL_ARRAY_BUFFER, 
                     shapes::k_cube.size() * sizeof(GLfloat), 
                     shapes::k_cube.data(), 
                     GL_STATIC_DRAW);

        glEnableVertexAttribArray(k_shaderPositionIndex);
        glVertexAttribPointer(k_shaderPositionIndex,
                              3, 
                              GL_FLOAT, 
                              GL_FALSE, 
                              3 * sizeof(GLfloat), 
                              nullptr);

    }

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void draw()
{
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, -10.0f),
                                 glm::vec3(0.0f, 0.0f, 0.0f),
                                 glm::vec3(0.0f, 1.0f, 0.0f));
    glad_glUseProgram(CanvasData::get().shaderProgram);
    glad_glUniformMatrix4fv(glad_glGetUniformLocation(CanvasData::get().shaderProgram, "mvp"), 1, GL_FALSE, &view[0][0]);
    glBindVertexArray(s_cubeVao);
    glDrawArrays(GL_TRIANGLES, 0, shapes::k_cube.size() / 3);
    glBindVertexArray(0);
}

void terminate()
{
    glBindVertexArray(s_cubeVao);
    glDisableVertexAttribArray(k_shaderPositionIndex);
    glDeleteBuffers(1, &s_cubeVbo);
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &s_cubeVao);
}

}