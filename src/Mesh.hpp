#ifndef COFFEE_MESH_HPP
#define COFFEE_MESH_HPP

#include <cstdint>
#include <vector>

namespace coffee
{

struct Mesh
{
    unsigned vbo;
    unsigned vao;
    uint32_t vertexCount;
};

namespace mesh
{

Mesh create(const std::vector<float> &vertices);
void clean(const Mesh &mesh);

}

}

#endif