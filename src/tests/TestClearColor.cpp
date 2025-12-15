#include "tests/TestClearColor.h"
#include "glad/glad.h"
#include "imgui/imgui.h"

#include "Renderer.h"

namespace test {

TestClearColor::TestClearColor(const std::string& name, ResourceManager& resourceManager, Scene& scene)
    : Test(name, resourceManager, scene), m_ClearColor{ 0.2f, 0.3f, 0.3f }
{}

TestClearColor::~TestClearColor()
{}

void TestClearColor::OnAttach(Renderer& renderer, ResourceManager& resourceManager, Scene& scene)
{
    // Add the widget when the test becomes active
    renderer.AddDevWindowWidget<ImguiColorEdit3>("Clear Color", reinterpret_cast<glm::vec3*>(&m_ClearColor)); // Cast float[4] to ImVec4*
}
    
void TestClearColor::OnUpdate(float deltaTime)  
{
    
    if(m_PartyTime)
    {
        m_Time += deltaTime;
        float t = m_Time * m_Speed;
        m_ClearColor[0] = 0.5f + 0.5f * std::cos(t + 2.0f);
        m_ClearColor[1] = 0.5f + 0.5f * std::cos(t + 0.0f);
        m_ClearColor[2] = 0.5f + 0.5f * std::cos(t + 4.189f);
    }
}

void TestClearColor::OnRender(Renderer& renderer) 
{
    // Apply clear color while active (takes effect on next frame's clear).
    renderer.SetClearColor(m_ClearColor);
}

void TestClearColor::OnImGuiRender(Renderer& renderer)  
{
    if(ImGui::Button("Reset Color"))
    {
        ResetColor(renderer);
        renderer.EnableDevWindowWidget("Clear Color");
    }
    
    if(ImGui::Checkbox("Party Time", &m_CheckboxState))
    {
        if(m_CheckboxState == true)
        {
            renderer.DisableDevWindowWidget("Clear Color");
            m_PartyTime = true;
        } else {
            renderer.EnableDevWindowWidget("Clear Color");
            m_PartyTime = false;
        }
    }   
    
}

void TestClearColor::OnDetach(Renderer& renderer)
{
    // Central cleanup happens on test switch/back.
}

void TestClearColor::ResetColor(Renderer& renderer)
    {
        m_CheckboxState = false;
        m_PartyTime = false;
        m_ClearColor = renderer.GetWindowDefaultColor();
        
    }

/*--- End of test namespace-----------------------------------------------------------------*/
}
