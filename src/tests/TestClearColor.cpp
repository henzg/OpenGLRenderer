#include "tests/TestClearColor.h"
#include "glad/glad.h"
#include "imgui/imgui.h"

#include "Renderer.h"

namespace test {

TestClearColor::TestClearColor(const std::string& name)
    : Test(name), m_ClearColor{ 0.2f, 0.3f, 0.8f, 1.0f }
{}

TestClearColor::~TestClearColor()
{

}
    
TestClearColor::~TestClearColor()
{}
    
void TestClearColor::OnUpdate(float deltaTime)  
{}

void TestClearColor::OnRender() 
{
    glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]);
    glClear(GL_COLOR_BUFFER_BIT);  
}
void TestClearColor::OnImGuiRender(Renderer& renderer)  
{
    renderer.AddDevWindowWidget<ImguiColorPicker4>("Clear Color", m_ClearColor);    
}
/*--- End of test namespace-----------------------------------------------------------------*/
}
