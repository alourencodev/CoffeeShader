#include "Shader.hpp"

#include <array>
#include <fstream>
#include <functional>
#include <glad/glad.h>
#include <iostream>
#include <sstream>

#include "Constants.hpp"
#include "Utils/GL.hpp"
#include "Utils/Log.hpp"

namespace coffee::shader
{

constexpr char k_logTag[] = "Shader";
constexpr char k_mvpUniform[] = "uMVP";
constexpr GLsizei k_maxUniformNameLength = 64;

// TODO: Check if it is reliable to use GL_MAX_UNIFORM_LOCATIONS
// https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glGet.xhtml
constexpr size_t k_maxUniformBytes = 256;

#define TYPE_UNIFORM(uniform_sufix, cast_type) \
[](GLuint location, void *value) -> void \
{ \
    glUniform1 ## uniform_sufix(location, *reinterpret_cast<cast_type *>(value)); \
}

#define TYPE_UNIFORM_2(uniform_sufix, cast_type) \
[](GLuint location, void *value) -> void \
{ \
    auto castedValue = reinterpret_cast<cast_type *>(value); \
    glUniform2 ## uniform_sufix(location, castedValue[0], castedValue[1]); \
}

#define TYPE_UNIFORM_3(uniform_sufix, cast_type) \
[](GLuint location, void *value) -> void \
{ \
    auto castedValue = reinterpret_cast<cast_type *>(value); \
    glUniform3 ## uniform_sufix(location, castedValue[0], castedValue[1], castedValue[2]); \
}

#define TYPE_UNIFORM_4(uniform_sufix, cast_type) \
[](GLuint location, void *value) -> void \
{ \
    auto castedValue = reinterpret_cast<cast_type *>(value); \
    glUniform4 ## uniform_sufix(location, castedValue[0], castedValue[1], castedValue[2], castedValue[3]); \
}

using TypeUniformFunctionMap = std::unordered_map<GLenum, std::function<void(GLuint, void *)>>;
static TypeUniformFunctionMap s_uniformFunctionMap =
{
    {GL_INT,                TYPE_UNIFORM(i, int)},
    {GL_INT_VEC2,           TYPE_UNIFORM_2(i, int)},
    {GL_INT_VEC3,           TYPE_UNIFORM_3(i, int)},
    {GL_INT_VEC4,           TYPE_UNIFORM_4(i, int)},
    {GL_FLOAT,              TYPE_UNIFORM(f, float)},
    {GL_FLOAT_VEC2,         TYPE_UNIFORM_2(f, float)},
    {GL_FLOAT_VEC3,         TYPE_UNIFORM_3(f, float)},
    {GL_FLOAT_VEC4,         TYPE_UNIFORM_4(f, float)},
};

static std::string loadShader(const std::string &dir)
{
    std::ifstream file(dir);
        
    if (!file.is_open()) {
        logFatal(k_logTag, "Unable to open file %s.", dir);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}

static GLuint compileShader(GLenum shaderType, const std::string &source)
{
    GLuint shaderId = glCreateShader(shaderType);
    const char *shaderSource = source.c_str();
    const GLint sourceSize = source.size();

    glShaderSource(shaderId, 1, &shaderSource, &sourceSize);
    glCompileShader(shaderId);

    GLint success = 0;
    char error[128] = "";
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE)
    {
    	glGetShaderInfoLog(shaderId, sizeof(error), NULL, error);
        logError(k_logTag, "Shader compilation error:\n%s", error);
    }

    return shaderId;
}

static GLuint linkProgram(GLuint vertShaderId, GLuint fragShaderId)
{
    GLuint programID = glCreateProgram();

    glAttachShader(programID, vertShaderId);
    glAttachShader(programID, fragShaderId);
    glLinkProgram(programID);

    GLint success = 0;
    char error[128] = "";
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (success == GL_FALSE)
    {
    	glGetProgramInfoLog(programID, sizeof(error), NULL, error);
        logError(k_logTag, "Shader program linking error:\n%s", error);
    }

    return programID;
}

void setupUniforms(Shader &shader)
{
    static std::array<char, k_maxUniformBytes> s_uniformValuesStack = {};
    unsigned s_uniformStackPointer = 0;

    s_uniformStackPointer = 0;
    GLint count;
    glGetProgramiv(shader.programId, GL_ACTIVE_UNIFORMS, &count);

    shader.uniforms.reserve(count);
    shader.uniformNames.reserve(count);

    for (GLuint i = 0; i < count; i++) {
        GLchar buffer[k_maxUniformNameLength];
        GLenum type;

        GLsizei length, size; // Dummies
        glGetActiveUniform(shader.programId, i, k_maxUniformNameLength, &length, &size, &type, buffer);

        int32_t uniformBytes = utils::sizeofGLType(type);
        if (uniformBytes > 0) {
            std::string name = std::string(buffer);
            GLuint location = glGetUniformLocation(shader.programId, buffer);

            Uniform uniform = {&s_uniformValuesStack[s_uniformStackPointer], type, location};
            shader.uniforms.emplace_back(uniform);
            shader.uniformNames.emplace_back(name);
            s_uniformStackPointer += uniformBytes;

            if (s_uniformStackPointer >= k_maxUniformBytes) {
                logError(k_logTag, 
                         "Unoform buffer overflow. Can't have more than %d total bytes within the editable uniforms", k_maxUniformBytes);
                break;
            }
        }
    }
}

Shader create(const std::string &vertexDir, const std::string &fragmentDir)
{
    std::string vertSource = loadShader(vertexDir);
    std::string fragSource = loadShader(fragmentDir);

    GLuint vertShaderId = compileShader(GL_VERTEX_SHADER, vertSource);
    GLuint fragShaderId = compileShader(GL_FRAGMENT_SHADER, fragSource);

    Shader shader = {};
    shader.programId = linkProgram(vertShaderId, fragShaderId);
    shader.mvpIndex = glGetUniformLocation(shader.programId, k_mvpUniform);
    setupUniforms(shader);

    glDeleteShader(vertShaderId);
    glDeleteShader(fragShaderId);

    return shader;
}
    
void use(const Shader &shader)
{
    glUseProgram(shader.programId);
}

void updateUniforms(const Shader &shader)
{
    for (const auto &uniform : shader.uniforms) {
        if (s_uniformFunctionMap.find(uniform.type) != s_uniformFunctionMap.end()) {
            s_uniformFunctionMap[uniform.type](uniform.location, uniform.valuePtr);
        }
    }
}

void terminate(const Shader &shader)
{
    glDeleteProgram(shader.programId);
}

}