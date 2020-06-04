#ifndef COFFEE_MESH_HPP
#define COFFEE_MESH_HPP

#include <cstdint>
#include <glm/vec3.hpp>
#include <vector>

namespace coffee
{

struct Mesh
{
    unsigned vertexBuffer;
    unsigned normalBuffer;
    unsigned vao;
    uint32_t vertexCount;
};

namespace mesh
{

Mesh create(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec3> &normals);
void clean(const Mesh &mesh);

}

}

#endif