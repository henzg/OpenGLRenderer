#include "DeveloperWindow.h"

DeveloperWindow::DeveloperWindow(const std::string& title, ImVec2 initialPos, ImVec2 initialSize) 
    : m_title(title), m_position(initialPos), m_size(initialSize) {}

void DeveloperWindow::BindFloat(const char* label, float* value, float min, float max)
{
    m_floatLabel = label;
    m_floatPtr = value;
    m_floatMin = min;
    m_floatMax = max;
}

void DeveloperWindow::Draw()
{
    ImGui::SetNextWindowPos(m_position, ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(m_size, ImGuiCond_FirstUseEver);

    ImGui::Begin(m_title.c_str());
    ImGui::Text("Hello from the Developer Window!");
    
    if(m_floatLabel && m_floatPtr)
        ImGui::SliderFloat(m_floatLabel, m_floatPtr, m_floatMin, m_floatMax);
    
    ImGui::End();
}
