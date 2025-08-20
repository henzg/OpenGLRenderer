#include "ImGuiSystem.h"

ImGuiSystem::ImGuiSystem(GLFWwindow* window, bool enableDocking, bool enableViewports, const char* glsl_version)
    : m_Window(window), m_ViewportBackup(nullptr)
{
    // context
    IMGUI_CHECKVERSION();
    m_Context = ImGui::CreateContext();
    ImGui::SetCurrentContext(m_Context);

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    //if (enableDocking) io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    //if (enableViewports) io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    // style
    if (enableViewports)
    {
        ImGuiStyle& style = ImGui::GetStyle();
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.f;
    }

    // Backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

ImGuiSystem::~ImGuiSystem()
{
    // shutdown in reverse order
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext(m_Context);
}

// call once per fram before any Begin
void ImGuiSystem::begin_frame()
{
    ImGui::SetCurrentContext(m_Context);
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

// once perframe after all windows have drawn
void ImGuiSystem::end_frame()
{
    ImGui::SetCurrentContext(m_Context);
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

