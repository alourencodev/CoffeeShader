#include "Mesh.hpp"

#include <glad/glad.h>

#include "Core/Assert.hpp"

namespace coffee::mesh
{

constexpr uint32_t k_positionAttribIndex = 0;
constexpr uint32_t k_normalAttribIndex = 1;
constexpr uint32_t k_vertexSize = 3 * sizeof(GLfloat);

Mesh create(const std::vector<float> &vertices, const std::vector<float> &normals)
{
    ASSERT_MSG(!vertices.empty(), "Trying to create mesh with no vertices.");
    ASSERT_MSG(!normals.empty(), "Trying to create mesh with no normals.");

    Mesh mesh = {};
    glGenVertexArrays(1, &mesh.vao);
    glBindVertexArray(mesh.vao);
    {
        {   // VertexBuffer
            glGenBuffers(1, &mesh.vertexBuffer);
            glBindBuffer(GL_ARRAY_BUFFER, mesh.vertexBuffer);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
            glEnableVertexAttribArray(k_positionAttribIndex);
            glVertexAttribPointer(k_positionAttribIndex, 3, GL_FLOAT, GL_FALSE, k_vertexSize, nullptr);
        }

        {   // NormalBuffer
            glGenBuffers(1, &mesh.normalBuffer);
            glBindBuffer(GL_ARRAY_BUFFER, mesh.normalBuffer);
            glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(GLfloat), normals.data(), GL_STATIC_DRAW);
            glEnableVertexAttribArray(k_normalAttribIndex);
            glVertexAttribPointer(k_normalAttribIndex, 3, GL_FLOAT, GL_FALSE, k_vertexSize, nullptr);
        }
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
    glDisableVertexAttribArray(k_normalAttribIndex);
    glDeleteBuffers(1, &mesh.vertexBuffer);
    glDeleteBuffers(2, &mesh.normalBuffer);
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &mesh.vao);
}

} 