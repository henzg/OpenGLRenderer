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
{}

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
        m_ClearColor[0] = 0.2f;
        m_ClearColor[1] = 0.3f;
        m_ClearColor[2] = 0.3f;
        m_ClearColor[3] = 1.0f;
    }

/*--- End of test namespace-----------------------------------------------------------------*/
}
