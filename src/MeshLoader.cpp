#include "MeshLoader.hpp"

#include <glad/glad.h>

namespace coffee
{

constexpr uint32_t k_positionAttribIndex = 0;
constexpr uint32_t k_vertexSize = 3 * sizeof(GLfloat);

Mesh createMesh(const std::vector<float> &vertices)
{
    Mesh mesh = {};
    glad_glGenVertexArrays(1, &mesh.vao);
    glad_glBindVertexArray(mesh.vao);
    {
        glad_glGenBuffers(1, &mesh.vbo);
        glad_glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
        glad_glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
        glad_glEnableVertexAttribArray(k_positionAttribIndex);
        glad_glVertexAttribPointer(k_positionAttribIndex, 3, GL_FLOAT, GL_FALSE, k_vertexSize, nullptr);
        glad_glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    glad_glBindVertexArray(0);
    mesh.vertexCount = vertices.size() / 3;

    return mesh;
}

void cleanMesh(const Mesh &mesh)
{
    glad_glBindVertexArray(mesh.vao);
    glad_glDisableVertexAttribArray(k_positionAttribIndex);
    glad_glDeleteBuffers(1, &mesh.vbo);
    glad_glBindVertexArray(0);
    glad_glDeleteVertexArrays(1, &mesh.vao);
}

}