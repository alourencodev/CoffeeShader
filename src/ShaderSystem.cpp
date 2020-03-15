#include "ShaderSystem.hpp"

#include <fstream> 
#include <iostream>
#include <sstream>

namespace coffee::shaderSystem
{

void setShader(const std::string &vertexDir, const std::string &fragmentDir)
{
    auto loadShader = [](const std::string &dir) -> std::string
    {
        std::ifstream file(dir);
        
        if (!file.is_open()) {
            std::cerr << "ERROR Unable to open file " << dir << "!" << std::endl;
        }

        std::stringstream buffer;
        buffer << file.rdbuf();

        return buffer.str();
    };

    std::string vertexSource = loadShader(vertexDir);
    std::string fragmentSource = loadShader(fragmentDir);
}
    
}