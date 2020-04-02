#include "ShaderLoader.hpp"

#include <fstream> 
#include <glad/glad.h>
#include <iostream>
#include <sstream>

#include "Constants.hpp"

namespace coffee
{

Shader loadShader(const std::string &vertexDir, const std::string &fragmentDir)
{
    auto loadShader = [](const std::string &dir) -> std::string
    {
        std::ifstream file(dir);
        
        if (!file.is_open()) {
            std::cerr << "ERROR Unable to open file " << dir << "!" << std::endl;
            std::exit(1);
        }

        std::stringstream buffer;
        buffer << file.rdbuf();

        return buffer.str();
    };

    auto compileShader = [](GLenum shaderType, const std::string &source) -> GLuint
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
			std::cerr << "Error Compiling shader:\n" << error << std::endl;
            std::exit(1);
		}
        
        return shaderId;
    };

    auto linkProgram = [](GLuint vertShaderId, GLuint fragShaderId) -> GLuint
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
			std::cerr << "Error Linking shader program:\n" << error << std::endl;
            std::exit(1);
		}

        return programID;
    };

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
    
}