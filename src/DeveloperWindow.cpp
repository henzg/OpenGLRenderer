#include "DeveloperWindow.h"

DeveloperWindow::DeveloperWindow(const std::string& title, ImVec2 initialPos, ImVec2 initialSize) 
    : m_title(title), m_position(initialPos), m_size(initialSize) {}

void DeveloperWindow::Draw()
{
    ImGui::SetNextWindowPos(m_position, ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(m_size, ImGuiCond_FirstUseEver);

    ImGui::Begin(m_title.c_str());
    ImGui::Text("Hello from the Developer Window!");
    ImGui::End();
}
