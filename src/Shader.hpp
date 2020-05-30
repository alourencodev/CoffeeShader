#ifndef COFFEE_SHADER_HPP
#define COFFEE_SHADER_HPP

#include <string>
#include <vector>

namespace coffee
{

enum class ShaderStage : uint8_t
{
    eVertex,
    eFragment
};

struct Uniform
{
    void *valuePtr;
    unsigned type; // GLenum
    unsigned location;
};

struct Shader
{
    unsigned programId;
    unsigned mvpIndex;
    std::vector<std::string> uniformNames;
    std::vector<Uniform> uniforms;
};

namespace shader
{

constexpr uint32_t k_positionsAttribIndex = 0;
constexpr uint32_t k_normalsAttribIndex = 1;

bool create(Shader *outShader, const std::string &vertSource, const std::string &fragSource);
void use(const Shader &shader);
void updateUniforms(const Shader &shader);
void terminate(const Shader &shader);

}

}

#endif
