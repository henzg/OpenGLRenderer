#include "tests/TestClearColor.h"
#include "glad/glad.h"
#include "imgui/imgui.h"

#include "Renderer.h"

namespace test {

TestClearColor::TestClearColor(const std::string& name)
    : Test(name), m_ClearColor{ 0.2f, 0.3f, 0.3f, 1.0f }
{}

TestClearColor::~TestClearColor()
{}

void TestClearColor::OnAttach(Renderer& renderer)
{
    // Add the widget when the test becomes active
    renderer.AddDevWindowWidget<ImguiColorEdit4>("Clear Color", reinterpret_cast<ImVec4*>(&m_ClearColor)); // Cast float[4] to ImVec4*
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
    glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]);
    glClear(GL_COLOR_BUFFER_BIT);  
}

void TestClearColor::OnImGuiRender(Renderer& renderer)  
{
    if(ImGui::Button("Reset Color"))
    {
        ResetColor();
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
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    renderer.RemoveDevWindowWidget("Clear Color");
}

void TestClearColor::ResetColor()
    {
        m_CheckboxState = false;
        m_PartyTime = false;
        
        m_ClearColor[0] = 0.2f;
        m_ClearColor[1] = 0.3f;
        m_ClearColor[2] = 0.3f;
        m_ClearColor[3] = 1.0f;
    }

/*--- End of test namespace-----------------------------------------------------------------*/
}
