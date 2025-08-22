#include "DeveloperWindow.h"
#include <iostream>


DeveloperWindow::DeveloperWindow(const std::string& title, ImVec2 initialPos, ImVec2 initialSize) 
    : m_Title(title), m_Position(initialPos), m_Size(initialSize) 
{
    ImGui::SetNextWindowPos(m_Position, ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(m_Size, ImGuiCond_FirstUseEver);
}


void DeveloperWindow::Draw()
{
    ImGui::Begin(m_Title.c_str());
    ImGui::Text("Hello from the Developer Window!");
    
    for (const auto& widget : m_Widgets)
    {
        widget->Draw();
    }

    ImGui::End();
}
