#include "tests/TestTriangle.h"

#include "ImguiWidget.h"
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
        VertexBufferLayout layout = {
            {ShaderDataType::Float3, "aPos"},
        };

        // Create a real Mesh so we can use the Entity pipeline.
        m_ResourceManager->AddMesh("TriangleMesh", m_Verticies, 3, m_TriangleIndicies, 3, layout);
        m_ResourceManager->AddShader("BasicShader", m_VertexShaderPath, m_FragmentShaderPath);

        m_Mesh = m_ResourceManager->GetMesh("TriangleMesh");
        m_Shader = m_ResourceManager->GetShader("BasicShader");

        // Entity (projection/view/model set automatically; this shader ignores them)
        Scene::Entity e{};
        e.mesh = m_Mesh;
        e.shader = m_Shader;
        e.bind = [this](Shader& shader, const Renderer&) {
            shader.setVec4("TriangleColor", m_TriangleColor);
            shader.setVec2("triPos", m_TriCoords);
        };
        scene.AddEntity(e);

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
        // Draw is handled by Scene::Entity in Renderer::OnRender(scene)
        // Keep wireframe state here (global state), since it affects rendering.
        if(m_ShowTriWireFrame)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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
        m_Mesh = nullptr;
        m_Shader = nullptr;
    }


/*--- End of test namespace-----------------------------------------------------------------*/
}
