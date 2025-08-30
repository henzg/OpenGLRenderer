#include "DeveloperWindow.h"


DeveloperWindow::DeveloperWindow(const std::string& title, test::Test*& currentTestPointer,ImVec2 initialPos, ImVec2 initialSize) 
    : m_Title(title), m_CurrentTest(currentTestPointer), m_Position(initialPos), m_Size(initialSize) 
{
    ImGui::SetNextWindowPos(m_Position, ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(m_Size, ImGuiCond_FirstUseEver);
}


void DeveloperWindow::Draw(int mainWindowWidth, int mainWindowHeight)
{

    float panelWidth = 400.0f;
    float panelHeight = static_cast<float>(mainWindowHeight);
    float panelPosX = static_cast<float>(mainWindowWidth) - (panelWidth);
    float panelPosY = 0.0f;

    ImGui::SetNextWindowPos(ImVec2(panelPosX, panelPosY), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(panelWidth, panelHeight), ImGuiCond_Always);

    ImGui::Begin(m_Title.c_str(), nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                 ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoBackground);
    
    for (auto& test : m_Tests)
    {
        if(ImGui::Button(test.first.c_str()))
            m_CurrentTest = test.second(); // returns new test pointer for us
    }

    for (const auto& widget : m_Widgets)
    {
        widget->Draw();
    }

    ImGui::End();
}

void DeveloperWindow::ClearWidgets()
{
    m_Widgets.clear();
}
