#include "Renderer.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

#include "Data/Canvas.hpp"
#include "Data/Shapes.hpp"
#include "Data/Context.hpp"

namespace coffee::renderer
{

static const GLuint k_shaderPositionIndex = 0; 

static GLuint s_cubeVao;
static GLuint s_cubeVbo;

static glm::mat4 s_mvp;

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

    glm::mat4 view = glm::lookAt(glm::vec3(4.0f, 3.0f, 3.0f),
                                 glm::vec3(0.0f, 0.0f, 0.0f),
                                 glm::vec3(0.0f, 1.0f, 0.0f));

    auto windowSize = Context::get().windowSize;
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 
                                            static_cast<float>(windowSize.x) / static_cast<float>(windowSize.y),
                                            0.1f, 100.0f);

    s_mvp = projection * view * glm::mat4(1.0f);
}

void draw()
{
    glUseProgram(Canvas::get().shaderProgram);
    glUniformMatrix4fv(glad_glGetUniformLocation(Canvas::get().shaderProgram, "mvp"), 1, GL_FALSE, &s_mvp[0][0]);
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