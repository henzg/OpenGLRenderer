#include "tests/TestTriangle.h"

#include "ImguiWidget.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"

#include "imgui/imgui.h"
namespace test
{
TestTriangle::TestTriangle(const std::string& name, ResourceManager& resourceManager, Scene& scene)
    : Test(name, resourceManager, scene), m_ResourceManager(&resourceManager), m_TriangleColor(1.0, 0.5, 0.2, 1.0)
{}

    TestTriangle::~TestTriangle() {}

    void TestTriangle::OnAttach(Renderer& renderer, ResourceManager& resourceManager, Scene& scene)
    {
        m_ResourceManager->AddVertexArray("TriangleVAO");
        m_ResourceManager->AddVertexBuffer("TriangleVBO", m_Verticies, sizeof(m_Verticies));
        
        VertexBufferLayout layout = 
        {
            {ShaderDataType::Float3, "aPos"},
        };

        m_ResourceManager->GetVertexArray("TriangleVAO")->AddBuffer(*m_ResourceManager->GetVertexBuffer("TriangleVBO"), layout);
        m_ResourceManager->AddIndexBuffer("TriangleEBO", m_TriangleIndicies, 3);
        m_ResourceManager->AddShader("BasicShader", m_VertexShaderPath, m_FragmentShaderPath);

        m_VAO = m_ResourceManager->GetVertexArray("TriangleVAO");
        m_VBO = m_ResourceManager->GetVertexBuffer("TriangleVBO");
        m_IndexBuffer = m_ResourceManager->GetIndexBuffer("TriangleEBO");
        m_Shader = m_ResourceManager->GetShader("BasicShader");

        renderer.AddDevWindowWidget<ImguiColorEdit4>("Triangle Color",
                                                     reinterpret_cast<ImVec4*>(&m_TriangleColor));
        renderer.AddDevWindowWidget<ImguiDragFloat2>("Position", &m_TriCoords, .01);
        
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
        if(m_ShowTriWireFrame)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        m_VAO->Bind();
        m_IndexBuffer->Bind();
        m_Shader->Bind();
        m_Shader->setVec4("TriangleColor", m_TriangleColor);
        m_Shader->setVec2("triPos", m_TriCoords);

        // Calculate matrices (Model, View, Projection)
        glm::mat4 projection = glm::perspective(glm::radians(renderer.GetCameraZoom()), 
                                                (float)renderer.GetWindowWidth() / (float)renderer.GetWindowHeight(), 0.1f, 100.f);
        glm::mat4 view = renderer.GetCameraViewMatrix();
        glm::mat4 model = glm::mat4(1.0f); // Simple identity model matrix for now

        m_Shader->setMat4("projection", projection);
        m_Shader->setMat4("view", view);
        m_Shader->setMat4("model", model);

        glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
        
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
                renderer.DisableDevWindowWidget("Triangle Color");
                m_PartyTime = true;
            } else {
                renderer.EnableDevWindowWidget("Triangle Color");
                m_PartyTime = false;
            }
        }   
    }
    void TestTriangle::OnDetach(Renderer& renderer) 
    {
        renderer.RemoveDevWindowWidget("Triangle Color");
        renderer.SetClearColor(renderer.GetWindowDefaultColor());
        renderer.RemoveDevWindowWidget("Position");
        m_ResourceManager->ClearVertexArrays();
        m_ResourceManager->ClearVertexBuffers();
        m_ResourceManager->ClearIndexBuffers();
        m_ResourceManager->ClearShaders();

    }


/*--- End of test namespace-----------------------------------------------------------------*/
}
