#include "Shader.hpp"

#include <fstream> 
#include <glad/glad.h>
#include <iostream>
#include <sstream>

#include "Constants.hpp"
#include "Utils/Log.hpp"

namespace coffee::shader
{

constexpr char k_logTag[] = "Shader";

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

Shader create(const std::string &vertexDir, const std::string &fragmentDir)
{
    std::string vertSource = loadShader(vertexDir);
    std::string fragSource = loadShader(fragmentDir);

    GLuint vertShaderId = compileShader(GL_VERTEX_SHADER, vertSource);
    GLuint fragShaderId = compileShader(GL_FRAGMENT_SHADER, fragSource);

    Shader shader = {};
    shader.programId = linkProgram(vertShaderId, fragShaderId);
    shader.mvpIndex = glGetUniformLocation(shader.programId, constants::shader::k_mvpUniform);

    glDeleteShader(vertShaderId);
    glDeleteShader(fragShaderId);

    return shader;
}
    
void use(const Shader &shader)
{
    glUseProgram(shader.programId);
}

void terminate(const Shader &shader)
{
    glDeleteProgram(shader.programId);
}

}