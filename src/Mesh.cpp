#include "Mesh.hpp"

#include <glad/glad.h>

namespace coffee::mesh
{

constexpr uint32_t k_positionAttribIndex = 0;
constexpr uint32_t k_vertexSize = 3 * sizeof(GLfloat);

Mesh create(const std::vector<float> &vertices)
{
    Mesh mesh = {};
    glGenVertexArrays(1, &mesh.vao);
    glBindVertexArray(mesh.vao);
    {
        glGenBuffers(1, &mesh.vbo);
        glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
        glEnableVertexAttribArray(k_positionAttribIndex);
        glVertexAttribPointer(k_positionAttribIndex, 3, GL_FLOAT, GL_FALSE, k_vertexSize, nullptr);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    glBindVertexArray(0);
    mesh.vertexCount = vertices.size() / 3;

    return mesh;
}

void clean(const Mesh &mesh)
{
    glBindVertexArray(mesh.vao);
    glDisableVertexAttribArray(k_positionAttribIndex);
    glDeleteBuffers(1, &mesh.vbo);
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &mesh.vao);
}

}