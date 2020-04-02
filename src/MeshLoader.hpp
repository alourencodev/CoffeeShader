#ifndef COFFEE_MESH_LOADER_HPP
#define COFFEE_MESH_LOADER_HPP

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

Mesh createMesh(const std::vector<float> &vertices);
void cleanMesh(const Mesh &mesh);

}

#endif