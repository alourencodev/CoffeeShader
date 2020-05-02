#include "Gui.hpp"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <functional>
#include <glad/glad.h>
#include <vector>

#include "Canvas.hpp"

namespace coffee::gui
{

constexpr char k_glslVersion[] = "#version 410";
constexpr float k_valueEditorDragSpeed = 0.1f;

static std::vector<std::function<void()>> s_activeGUIDrawFunction;
static Canvas *s_canvas = nullptr;

#define TYPE_EDITOR(imgui_call, cast_type) \
[](const char *label, void *value) -> void \
{ \
    ImGui::imgui_call(label, reinterpret_cast<cast_type *>(value), k_valueEditorDragSpeed); \
}

using TypeEditorFunctionMap = std::unordered_map<GLenum, std::function<void(const char *, void *)>>;
static TypeEditorFunctionMap s_typeEditorMap = 
{
    {GL_INT,                TYPE_EDITOR(DragInt, int)},
    {GL_INT_VEC2,           TYPE_EDITOR(DragInt2, int)},
    {GL_INT_VEC3,           TYPE_EDITOR(DragInt3, int)},
    {GL_INT_VEC4,           TYPE_EDITOR(DragInt4, int)},
    {GL_FLOAT,              TYPE_EDITOR(DragFloat, float)},
    {GL_FLOAT_VEC2,         TYPE_EDITOR(DragFloat2, float)},
    {GL_FLOAT_VEC3,         TYPE_EDITOR(DragFloat3, float)},
    {GL_FLOAT_VEC4,         TYPE_EDITOR(DragFloat4, float)}
};

static void drawInspector()
{
    ImGui::Begin("Inspector");

    const auto &uniforms = s_canvas->shader.uniforms;
    const auto &uniformNames = s_canvas->shader.uniformNames;
    for (int i = 0; i < uniforms.size(); i++) { 
        if (s_typeEditorMap.find(uniforms[i].type) != s_typeEditorMap.end()) {
            s_typeEditorMap[uniforms[i].type](uniformNames[i].c_str(), uniforms[i].valuePtr);
        }
    }

    ImGui::End();
}

void init(GLFWwindow *window, Canvas *canvas)
{   
        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(k_glslVersion);

        s_canvas = canvas;
        s_activeGUIDrawFunction.reserve(4);
        s_activeGUIDrawFunction.emplace_back(drawInspector);
}

void draw()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    for (auto drawFunction : s_activeGUIDrawFunction) {
        drawFunction();
    }

    ImGui::Render();
 
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void terminate()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

bool usedInput()
{
    return ImGui::GetIO().WantCaptureMouse;
}

}