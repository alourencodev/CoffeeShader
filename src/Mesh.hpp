#ifndef COFFEE_MESH_HPP
#define COFFEE_MESH_HPP

#include <cstdint>
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

Mesh create(const std::vector<float> &vertices, const std::vector<float> &normals);
void clean(const Mesh &mesh);

}

}

#endif