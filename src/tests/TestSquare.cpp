#include "tests/TestSquare.h"
#include "ImguiWidget.h"
#include "Renderer.h"   

#include "VertexBufferLayout.h"
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
        resourceManager.AddVertexArray("SquareVAO");
        resourceManager.AddVertexBuffer("SquareVBO", m_SquareVerticies, sizeof(m_SquareVerticies));
        resourceManager.AddIndexBuffer("SquareEBO", m_SquareIndicies, 6);
        resourceManager.AddShader("SquareShader", m_SquareVertexShader.c_str(), m_SquareFragmentShader.c_str());
        /*--- Add textures------------------------------------------------------------------*/
        resourceManager.AddTexture("woodTex", "../res/wood.png", false, false);
        resourceManager.AddTexture("awesomeFace", "../res/awesomeface.png", true, true);

        VertexBufferLayout squareLayout = { 
        {ShaderDataType::Float3, "aPos"},
        {ShaderDataType::Float2, "aTexture"},
        };
        resourceManager.GetVertexArray("SquareVAO")->AddBuffer(*resourceManager.GetVertexBuffer("SquareVBO"), squareLayout);

        m_VAO = resourceManager.GetVertexArray("SquareVAO");
        m_VBO = resourceManager.GetVertexBuffer("SquareVBO");
        m_IndexBuffer = resourceManager.GetIndexBuffer("SquareEBO");
        m_Shader = resourceManager.GetShader("SquareShader");
        m_Texture1 = resourceManager.GetTexture("woodTex");
        m_Texture2 = resourceManager.GetTexture("awesomeFace");

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
        
        Texture* tex1 = m_ResourceManager->GetTexture("woodTex");
        Texture* tex2 = m_ResourceManager->GetTexture("awesomeFace");
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
        
        // Calculate matrices (Model, View, Projection)
        glm::mat4 projection = glm::perspective(glm::radians(renderer.GetCameraZoom()), 
                                                (float)renderer.GetWindowWidth() / (float)renderer.GetWindowHeight(), 0.1f, 100.f);
        glm::mat4 view = renderer.GetCameraViewMatrix();
        glm::mat4 model = glm::mat4(1.0f); // Simple identity model matrix for now

        m_Shader->setMat4("projection", projection);
        m_Shader->setMat4("view", view);
        m_Shader->setMat4("model", model);
    
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
        m_ResourceManager->ClearTextures();
        m_ResourceManager->ClearVertexArrays();
        m_ResourceManager->ClearVertexBuffers();
        m_ResourceManager->ClearIndexBuffers();
        m_ResourceManager->ClearShaders();

    }
/*--- End of test namespace-----------------------------------------------------------------*/
}
