#ifndef COFFEE_OBJ_PARSER_HPP
#define COFFEE_OBJ_PARSER_HPP

#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <fstream>
#include <sstream>
#include <vector>

namespace coffee
{

struct Obj
{
    std::vector<glm::vec3> vertices = {};
    std::vector<glm::vec3> normals = {};
};

namespace obj
{

Obj load(std::ifstream &ifstream);

}
}

#endif
