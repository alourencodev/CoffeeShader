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

static float _;     // TRASH: This is temporaryk

constexpr char k_glslVersion[] = "#version 410";
constexpr float k_valueEditorDragSpeed = 1.0f;

static std::vector<std::function<void()>> s_activeGUIDrawFunction;
static Canvas *s_canvas = nullptr;

#define VALUE_EDITOR(imgui_call, cast_type) [](const char *label, void *value) -> void \
                                            { \
                                                ImGui::imgui_call(label, reinterpret_cast<cast_type *>(value), k_valueEditorDragSpeed); \
                                            }

using TypeWidgetDrawFunctionMap = std::unordered_map<GLenum, std::function<void(const char *, void *)>>;
static TypeWidgetDrawFunctionMap s_typeWidgetDrawMap = 
{
    {GL_INT,                VALUE_EDITOR(DragInt, int)},
    {GL_INT_VEC2,           VALUE_EDITOR(DragInt2, int)},
    {GL_INT_VEC3,           VALUE_EDITOR(DragInt3, int)},
    {GL_INT_VEC4,           VALUE_EDITOR(DragInt4, int)},
    {GL_FLOAT,              VALUE_EDITOR(DragFloat, float)},
    {GL_FLOAT_VEC2,         VALUE_EDITOR(DragFloat2, float)},
    {GL_FLOAT_VEC3,         VALUE_EDITOR(DragFloat3, float)},
    {GL_FLOAT_VEC4,         VALUE_EDITOR(DragFloat4, float)}
};

static void drawShaderEditor()
{
    ImGui::Begin("Inspector");

    for (auto uniform : s_canvas->shader.uniforms) {
        if (s_typeWidgetDrawMap.find(uniform.type) != s_typeWidgetDrawMap.end()) {
            s_typeWidgetDrawMap[uniform.type](uniform.name.c_str(), &_ /* TODO: Set Value here */);
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
        s_activeGUIDrawFunction.emplace_back(drawShaderEditor);
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

}