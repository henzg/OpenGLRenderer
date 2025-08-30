#include "DeveloperWindow.h"
//#include "Renderer.h"

DeveloperWindow::DeveloperWindow(const std::string& title,ImVec2 initialPos, ImVec2 initialSize) 
    : m_Title(title), m_Position(initialPos), m_Size(initialSize) 
{
    ImGui::SetNextWindowPos(m_Position, ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(m_Size, ImGuiCond_FirstUseEver);
}


void DeveloperWindow::Draw(int mainWindowWidth, int mainWindowHeight, Renderer& renderer, float deltaTime)
{

    float panelWidth = 300.0f;
    float panelHeight = static_cast<float>(mainWindowHeight);
    float panelPosX = static_cast<float>(mainWindowWidth) - (panelWidth);
    float panelPosY = 0.0f;

    ImGui::SetNextWindowPos(ImVec2(panelPosX, panelPosY), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(panelWidth, panelHeight), ImGuiCond_Always);

    ImGui::Begin(m_Title.c_str(), nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                 ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus); //| ImGuiWindowFlags_NoBackground);
    
    if(m_CurrentTest)
    {
        ImGui::Text("Current Test: %s", m_CurrentTest->GetName().c_str());
        if (ImGui::Button("<- Back to Menu"))
        {
            m_CurrentTest->OnDetach(renderer);
            m_CurrentTest.reset(); // deactive the current test if button is pressed
            ClearWidgets();
        }
        if(m_CurrentTest)
        {
            ImGui::Separator();
            for (const auto& widget : m_Widgets)
            {
                widget->Draw();
            }
            m_CurrentTest->OnImGuiRender(renderer);
            m_CurrentTest->OnUpdate(deltaTime); // openGL update/render methods
            m_CurrentTest->OnRender(renderer); 
        }
    }
    else // no test is active display the menu
    {
        ImGui::Text("Select a Test: ");
        for (const auto& testPair : m_Tests)
        {
            if(ImGui::Button(testPair.first.c_str()))
            {
                if(m_CurrentTest)
                    m_CurrentTest->OnDetach(renderer);
                m_CurrentTest = testPair.second(); // create and activate the new test
                m_CurrentTest->OnAttach(renderer);
            }
        }
    }


    ImGui::End();
}

void DeveloperWindow::ClearWidgets()
{
    m_Widgets.clear();
}

void DeveloperWindow::RemoveWidget(const std::string& label)
{
    auto it = std::remove_if(m_Widgets.begin(), m_Widgets.end(), [&](const std::unique_ptr<ImguiWidget>& widget) {
        return widget->GetLabel() == label;
    });
    m_Widgets.erase(it, m_Widgets.end());
}
