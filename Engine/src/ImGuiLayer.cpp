#include "ImGuiLayer.h"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"
#include "Application.h"

namespace Engine{

void ImGuiLayer::onAttach()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(Application::getApplication()->getWindow()->getWindow()
                                ,Application::getApplication()->getWindow()->getContext());
    ImGui_ImplOpenGL3_Init("#version 330");
}

void ImGuiLayer::onDetach()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void ImGuiLayer::onImGuiRender()
{
    bool show_demo = true;
    ImGui::ShowDemoWindow(&show_demo);
}

void ImGuiLayer::imGuiBegin()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(Application::getApplication()->getWindow()->getWindow());
    ImGui::NewFrame();
}

void ImGuiLayer::imGuiEnd()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiLayer::onEvent(Event &e)
{
    if (_blockevents)
    {
        ImGuiIO& io = ImGui::GetIO();
        e.setHandled(e.isHandled() | e.isInCategory(EventCategoryMouse) & io.WantCaptureMouse);
        e.setHandled(e.isHandled() | e.isInCategory(EventCategoryKeyboard) & io.WantCaptureKeyboard);
    }
}

}
