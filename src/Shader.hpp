#ifndef COFFEE_SHADER_HPP
#define COFFEE_SHADER_HPP

#include <string>

namespace coffee
{

struct Shader
{
    unsigned programId;
    unsigned mvpIndex;
};

namespace shader
{

Shader create(const std::string &vertexDir, const std::string &fragmentDir);
void use(unsigned programId);
void terminate(const Shader &shader);

}

}

#endif