#include "tests/TestTriangle.h"

#include "ImguiWidget.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"

#include "imgui/imgui.h"
namespace test
{
    TestTriangle::TestTriangle(const std::string& name)
        : Test(name), m_TriangleColor(1.0, 0.5, 0.2, 1.0)
    {}

    TestTriangle::~TestTriangle() {}

    void TestTriangle::OnAttach(Renderer& renderer)
    {

        m_VAO = std::make_unique<VertexArray>();
        m_VBO = std::make_unique<VertexBuffer>(m_Verticies, sizeof(m_Verticies));
        m_Shader = std::make_unique<Shader>(m_VertexShaderPath, m_FragmentShaderPath);
        
        VertexBufferLayout layout = 
        {
            {ShaderDataType::Float3, "aPos"},
        };

        m_VAO->AddBuffer(*m_VBO, layout);

        renderer.AddDevWindowWidget<ImguiColorEdit4>("Triangle Color",
                                                     reinterpret_cast<ImVec4*>(&m_TriangleColor));
        renderer.AddDevWindowWidget<ImguiDragFloat2>("Position", &m_TriCoords, .01);
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void TestTriangle::OnUpdate(float deltaTime) 
    {
       if(m_PartyTime)
        {
            m_Time += deltaTime;
            float t = m_Time * m_Speed;
            m_TriangleColor[0] = 0.5f + .5f * std::cos(t + 2.0f);
            m_TriangleColor[1] = .5f + .5f * std::cos(t + 0.1f);
            m_TriangleColor[2] = .5 + .5f * std::cos(t + 4.2f);
        }
    }
    void TestTriangle::OnRender(Renderer& renderer) 
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        if(m_ShowTriWireFrame)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        m_VAO->Bind();
        m_Shader->Bind();
        m_Shader->setVec4("TriangleColor", m_TriangleColor);
        m_Shader->setVec2("triPos", m_TriCoords);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
    }
    void TestTriangle::OnImGuiRender(Renderer& renderer) {
        if(ImGui::Checkbox("Wire Frame", &m_TriWireFrameState))
        {
            if(m_TriWireFrameState == true)
            {
                m_ShowTriWireFrame = true;
            } else 
                m_ShowTriWireFrame = false;
        }
        if(ImGui::Checkbox("Party Time", &m_TriCheckboxState))
        {
            if(m_TriCheckboxState == true)
            {
                renderer.DisableDevWindowWidget("TriangleColor");
                m_PartyTime = true;
            } else {
                renderer.EnableDevWindowWidget("TriangleColor");
                m_PartyTime = false;
            }
        }   
    }
    void TestTriangle::OnDetach(Renderer& renderer) 
    {
        m_VAO->Unbind();
        m_VBO->Unbind();
        m_Shader->Unbind();
        renderer.RemoveDevWindowWidget("Triangle Color");
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
    }


/*--- End of test namespace-----------------------------------------------------------------*/
}
