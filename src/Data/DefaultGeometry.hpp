#ifndef COFFEE_DEFAULT_GEOMETRY_HPP
#define COFFEE_DEFAULT_GEOMETRY_HPP

#include <vector>

namespace coffee::geometry
{

namespace cube
{
static const std::vector<glm::vec3> k_vertices = {glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3( 1.0f, -1.0f,  1.0f), glm::vec3(-1.0f, -1.0f,  1.0f),
                                                  glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec3(-1.0f,  1.0f,  1.0f),
                                                  glm::vec3(-1.0f,  1.0f,  1.0f), glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(-1.0f, -1.0f,  1.0f),
                                                  glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec3(-1.0f, -1.0f, -1.0f),
                                                  glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec3( 1.0f, -1.0f,  1.0f),
                                                  glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec3(-1.0f,  1.0f,  1.0f),
                                                  glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec3( 1.0f, -1.0f,  1.0f),
                                                  glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec3( 1.0f,  1.0f, -1.0f), glm::vec3(-1.0f,  1.0f, -1.0f),
                                                  glm::vec3(-1.0f,  1.0f,  1.0f), glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec3(-1.0f, -1.0f, -1.0f),
                                                  glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec3( 1.0f,  1.0f, -1.0f), glm::vec3( 1.0f, -1.0f, -1.0f),
                                                  glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec3( 1.0f,  1.0f, -1.0f), glm::vec3( 1.0f,  1.0f,  1.0f),
                                                  glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3( 1.0f, -1.0f,  1.0f), glm::vec3( 1.0f,  1.0f,  1.0f)};

static const std::vector<glm::vec3> k_normals = {glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec3( 0.0f, -1.0f,  0.0f),
                                                 glm::vec3( 0.0f,  1.0f, -0.0f), glm::vec3( 0.0f,  1.0f, -0.0f), glm::vec3( 0.0f,  1.0f, -0.0f),
                                                 glm::vec3(-1.0f, -0.0f,  0.0f), glm::vec3(-1.0f, -0.0f,  0.0f), glm::vec3(-1.0f, -0.0f,  0.0f),
                                                 glm::vec3( 0.0f, -0.0f, -1.0f), glm::vec3( 0.0f, -0.0f, -1.0f), glm::vec3( 0.0f, -0.0f, -1.0f),
                                                 glm::vec3( 1.0f, -0.0f,  0.0f), glm::vec3( 1.0f, -0.0f,  0.0f), glm::vec3( 1.0f, -0.0f,  0.0f),
                                                 glm::vec3(-0.0f,  0.0f,  1.0f), glm::vec3(-0.0f,  0.0f,  1.0f), glm::vec3(-0.0f,  0.0f,  1.0f),
                                                 glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec3( 0.0f, -1.0f,  0.0f),
                                                 glm::vec3( 0.0f,  1.0f, -0.0f), glm::vec3( 0.0f,  1.0f, -0.0f), glm::vec3( 0.0f,  1.0f, -0.0f),
                                                 glm::vec3(-1.0f, -0.0f,  0.0f), glm::vec3(-1.0f, -0.0f,  0.0f), glm::vec3(-1.0f, -0.0f,  0.0f),
                                                 glm::vec3( 0.0f, -0.0f, -1.0f), glm::vec3( 0.0f, -0.0f, -1.0f), glm::vec3( 0.0f, -0.0f, -1.0f),
                                                 glm::vec3( 1.0f, -0.0f,  0.0f), glm::vec3( 1.0f, -0.0f,  0.0f), glm::vec3( 1.0f, -0.0f,  0.0f),
                                                 glm::vec3(-0.0f,  0.0f,  1.0f), glm::vec3(-0.0f,  0.0f,  1.0f), glm::vec3(-0.0f,  0.0f,  1.0f)};

}
}

#endif