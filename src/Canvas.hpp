#ifndef COFFEE_CANVAS_HPP
#define COFFEE_CANVAS_HPP

#include <glm/glm.hpp>
#include <string>

#include "Camera.hpp"
#include "FileWatcher.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"

namespace coffee
{

struct Canvas
{
    Camera camera;
    Mesh mesh;
    Shader shader;
};

struct CanvasDescriptor
{
    struct ShaderFile
    {
        std::string dir = "";
        fileWatcher::WatchHandle watchHandle;
    };

    ShaderFile vertexFile;
    ShaderFile fragmentFile;
};

namespace canvas
{

Canvas create(const glm::ivec2 &windowSize);
void draw(const Canvas &canvas);
void terminate(const Canvas &canvas);

void setShader(Canvas *canvas, CanvasDescriptor *descriptor, const std::string &vertexDir, const std::string &fragmentDir);

}

}

#endif