#ifndef COFFEE_SHADER_LOADER_HPP
#define COFFEE_SHADER_LOADER_HPP

#include <string>

namespace coffee
{

struct Shader
{
    unsigned programId;
    unsigned mvpIndex;
};

Shader loadShader(const std::string &vertexDir, const std::string &fragmentDir);

}

#endif