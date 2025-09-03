#include "tests/TestSquare.h"
#include "ImguiWidget.h"
#include "Renderer.h"   

#include "VertexBufferLayout.h"
#include "imgui.h"

namespace test
{
    TestSquare::TestSquare(const std::string& name)
        : Test(name) {}
    TestSquare::~TestSquare() {}

    void TestSquare::OnAttach(Renderer& renderer)
    {
        /*--- Add Imgui widgets-------------------------------------------------------------*/
        renderer.AddDevWindowWidget<ImguiSliderFloat>("Texture Mix", &m_TextureMix, 0.f, 1.f);
        /*----------------------------------------------------------------------------------*/
        m_VAO = std::make_unique<VertexArray>();
        m_VBO = std::make_unique<VertexBuffer>(m_SquareVerticies, sizeof(m_SquareVerticies));
        m_IndexBuffer = std::make_unique<IndexBuffer>(m_SquareIndicies, 6);
        m_Shader = std::make_unique<Shader>(m_SquareVertexShader.c_str(), m_SquareFragmentShader.c_str());
        /*--- Add textures------------------------------------------------------------------*/
        renderer.AddTexture("woodTex", "../res/wood.png", false, false);
        renderer.AddTexture("awesomeFace", "../res/awesomeface.png", true, true);

        VertexBufferLayout squareLayout = { 
        {ShaderDataType::Float3, "aPos"},
        {ShaderDataType::Float2, "aTexture"},
        };
        m_VAO->AddBuffer(*m_VBO, squareLayout);

        if(m_Shader)
        {
            m_Shader->Bind();
            m_Shader->setInt("texture1", 0);
            m_Shader->setInt("texture2", 1);
        }
    }

    void TestSquare::OnUpdate(float deltaTime) {}
    void TestSquare::OnRender(Renderer& renderer) 
    {
        
        Texture* tex1 = renderer.GetTexture("woodTex");
        Texture* tex2 = renderer.GetTexture("awesomeFace");
        if (tex1) tex1->BindandActivate(GL_TEXTURE0);
        if (tex2) tex2->BindandActivate(GL_TEXTURE1);

        if(m_SquareWireFrame)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        m_VAO->Bind();
        m_IndexBuffer->Bind();
        m_Shader->Bind();
        m_Shader->setVec4("SquareColor", m_SquareColor);
        m_Shader->setFloat("textureMix", m_TextureMix);
    
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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
        //renderer.CleanUpResources();
        renderer.ClearDevWindowWidgets();
        renderer.ClearTextures();
    }
/*--- End of test namespace-----------------------------------------------------------------*/
}
