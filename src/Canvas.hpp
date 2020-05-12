#ifndef COFFEE_CANVAS_HPP
#define COFFEE_CANVAS_HPP

#include <glm/glm.hpp>
#include <string>
#include <utility>

#include "Camera.hpp"
#include "FileWatcher.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"

namespace coffee
{

enum class ShaderStage : uint8_t;

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
        std::string source = "";
        fileWatcher::WatchHandle watchHandle;
    };

    ShaderFile vertexFile;
    ShaderFile fragmentFile;
};

namespace canvas
{

// TODO: Get a better return for this
std::pair<Canvas, CanvasDescriptor> create(const glm::ivec2 &windowSize);
void draw(const Canvas &canvas);
void terminate(const Canvas &canvas);

void loadShader(Canvas *canvas, CanvasDescriptor *descriptor, const std::string &dir, ShaderStage stage);

}

}

#endif