#ifndef COFFEE_SHADER_HPP
#define COFFEE_SHADER_HPP

#include <string>
#include <vector>

namespace coffee
{

struct Uniform
{
    std::string name;
};

struct Shader
{
    unsigned programId;
    unsigned mvpIndex;
    std::vector<Uniform> uniforms;
};

namespace shader
{

Shader create(const std::string &vertexDir, const std::string &fragmentDir);
void use(const Shader &shader);
void terminate(const Shader &shader);

}

}

#endif