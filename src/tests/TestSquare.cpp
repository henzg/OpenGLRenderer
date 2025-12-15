#include "tests/TestSquare.h"
#include "ImguiWidget.h"
#include "Renderer.h"   

#include "imgui.h"

namespace test
{
    TestSquare::TestSquare(const std::string& name, ResourceManager& resourceManager, Scene& scene)
        : Test(name, resourceManager, scene), m_ResourceManager(&resourceManager) {}
    TestSquare::~TestSquare() {}

    void TestSquare::OnAttach(Renderer& renderer, ResourceManager& resourceManager, Scene& scene)
    {
        /*--- Add Imgui widgets-------------------------------------------------------------*/
        renderer.AddDevWindowWidget<ImguiSliderFloat>("Texture Mix", &m_TextureMix, 0.f, 1.f);
        /*----------------------------------------------------------------------------------*/
        VertexBufferLayout squareLayout = { 
        {ShaderDataType::Float3, "aPos"},
        {ShaderDataType::Float2, "aTexture"},
        };

        // Create a real Mesh so we can use the Entity pipeline.
        resourceManager.AddMesh("SquareMesh", m_SquareVerticies, 4, m_SquareIndicies, 6, squareLayout);
        resourceManager.AddShader("SquareShader", m_SquareVertexShader.c_str(), m_SquareFragmentShader.c_str());
        /*--- Add textures------------------------------------------------------------------*/
        resourceManager.AddTexture("woodTex", "../res/wood.png", false, false);
        resourceManager.AddTexture("awesomeFace", "../res/awesomeface.png", true, true);

        m_Mesh = resourceManager.GetMesh("SquareMesh");
        m_Shader = resourceManager.GetShader("SquareShader");
        m_Texture1 = resourceManager.GetTexture("woodTex");
        m_Texture2 = resourceManager.GetTexture("awesomeFace");

        if(m_Shader)
        {
            m_Shader->Bind();
            m_Shader->setInt("texture1", 0);
            m_Shader->setInt("texture2", 1);
        }

        // Entity (projection/view/model set automatically; this shader ignores them)
        Scene::Entity e{};
        e.mesh = m_Mesh;
        e.shader = m_Shader;
        e.bind = [this](Shader& shader, const Renderer&) {
                if (m_Texture1) m_Texture1->BindandActivate(GL_TEXTURE0);
                if (m_Texture2) m_Texture2->BindandActivate(GL_TEXTURE1);
                shader.setFloat("textureMix", m_TextureMix);
        };
        scene.AddEntity(e);
    }

    void TestSquare::OnUpdate(float deltaTime) {}
    void TestSquare::OnRender(Renderer& renderer) 
    {
        // Draw is handled by Scene::Entity in Renderer::OnRender(scene)
        if(m_SquareWireFrame)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    void TestSquare::OnImGuiRender(Renderer& renderer) 
    {
        if(ImGui::Checkbox("Show Wireframe", &m_ShowWireFrame))
        {
            if(m_ShowWireFrame == true)
            {
                m_SquareWireFrame = true;
            } else {
                m_SquareWireFrame = false;
            } 
            
        }
    }
void TestSquare::OnDetach(Renderer& renderer)
    {
        m_Mesh = nullptr;
        m_Shader = nullptr;
        m_Texture1 = nullptr;
        m_Texture2 = nullptr;

    }
/*--- End of test namespace-----------------------------------------------------------------*/
}
