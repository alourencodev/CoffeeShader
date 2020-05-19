#include "Gui.hpp"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <functional>
#include <glad/glad.h>
#include <osdialog/osdialog.h>
#include <string>
#include <vector>
#include <unordered_map>

#include "Canvas.hpp"
#include "Constants.hpp"
#include "Core/Log.hpp"
#include "Core/File.hpp"
#include "Shader.hpp"

namespace coffee::gui
{

constexpr char k_glslVersion[] = "#version 410";
constexpr float k_valueEditorDragSpeed = 0.1f;

#define TYPE_EDITOR(imgui_call, cast_type) \
[](const char *label, void *value) -> void \
{ \
    ImGui::imgui_call(label, reinterpret_cast<cast_type *>(value), k_valueEditorDragSpeed); \
}

static std::vector<std::function<void()>> s_activeGUIShowFunctions;
static std::vector<std::string> s_guiLogs;
static Canvas *s_canvas = nullptr;

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

static void showToolbar()
{
    auto showOpenShader = []() -> void
    {
        if (ImGui::MenuItem("Vertex")) {
            std::string dir; 
            if (file::openDialog(&dir)) {
                canvas::loadShader(s_canvas, dir, ShaderStage::eVertex);
            }
        }
        if (ImGui::MenuItem("Fragment")) {
            std::string dir; 
            if (file::openDialog(&dir)) {
                canvas::loadShader(s_canvas, dir, ShaderStage::eFragment);
            }
        }
        ImGui::EndMenu();
    };

    ImGui::BeginMainMenuBar();
    if (ImGui::BeginMenu("File")) {
        if (ImGui::BeginMenu("Open Shader")) {
            showOpenShader();
        }

        ImGui::EndMenu();
    } 
    if (ImGui::BeginMenu("Help")) {
        if (ImGui::MenuItem("About")) {
            // TODO
        }

        ImGui::EndMenu();
    }
    
    ImGui::EndMainMenuBar();
}

static void showUniformInspector()
{
    ImGui::Begin("Uniform Editor");

    const auto &uniforms = s_canvas->renderables.shader.uniforms;
    const auto &uniformNames = s_canvas->renderables.shader.uniformNames;
    for (int i = 0; i < uniforms.size(); i++) { 
        if (s_typeEditorMap.find(uniforms[i].type) != s_typeEditorMap.end()) {
            s_typeEditorMap[uniforms[i].type](uniformNames[i].c_str(), uniforms[i].valuePtr);
        }
    }

    ImGui::End();
}

static void showLogger()
{
    ImGui::SetNextWindowSize(ImVec2(600, 400));
    ImGui::Begin("Log");

    if (ImGui::Button("Clear")) {
        s_guiLogs.clear();
    }

    ImGui::Separator();
    ImGui::BeginChild("logScrollView");
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 1));

    for (const auto &log : s_guiLogs) {
        ImGui::TextUnformatted(log.c_str());
    }

    ImGui::SetScrollHere(1.0f);
    ImGui::PopStyleVar();
    ImGui::EndChild();
    ImGui::End();
}

void init(GLFWwindow *window, Canvas *canvas)
{   
        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(k_glslVersion);

        s_canvas = canvas;
        s_activeGUIShowFunctions.reserve(4);
        s_activeGUIShowFunctions.emplace_back(showUniformInspector);
        s_activeGUIShowFunctions.emplace_back(showToolbar);
        s_activeGUIShowFunctions.emplace_back(showLogger);
        
        s_guiLogs.reserve(10);
}

void draw()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    for (auto showFunction : s_activeGUIShowFunctions) {
        showFunction();
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

void log(const char *format, ...)
{
    char buffer[constants::k_maxLogSize];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    s_guiLogs.emplace_back(std::string(buffer));
}

}