#include "Gui.hpp"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <functional>
#include <vector>

namespace coffee::gui
{

constexpr char k_glslVersion[] = "#version 410";

static std::vector<std::function<void()>> s_activeGUIDrawFunction; 

void drawShaderEditor()
{
    ImGui::Begin("Inspector");
    ImGui::End();
}

void init(GLFWwindow *window)
{   
        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(k_glslVersion);
        
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