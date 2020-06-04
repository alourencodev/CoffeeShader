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
    struct Renderables
    {
        Camera camera;
        Mesh mesh;
        Shader shader;
    };

    struct Descriptor
    {
        struct ShaderFile
        {
            std::string source = "";
            fileWatcher::WatchHandle watchHandle;
        };

        ShaderFile vertexFile;
        ShaderFile fragmentFile;
    };

    Renderables renderables;
    Descriptor descriptor;
};

namespace canvas
{

Canvas create(const glm::ivec2 &windowSize);
void draw(const Canvas::Renderables &renderables);
void terminate(const Canvas &canvas);

void loadShader(Canvas *canvas, const std::string &dir, ShaderStage stage);
void loadObj(Canvas *canvas, const std::string &dir);
void onWindowResize(Canvas *canvas, int width, int height);
}

}

#endif