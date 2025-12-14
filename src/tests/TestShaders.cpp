#include "tests/TestShaders.h"
#include "ImguiWidget.h"
#include "Renderer.h"
#include <GLFW/glfw3.h>

namespace test
{
    TestShader::TestShader(const std::string& name, ResourceManager& resourceManager, Scene& scene)
        : Test(name, resourceManager, scene), m_ResourceManager(&resourceManager) {}
    TestShader::~TestShader() {}

    void TestShader::OnAttach(Renderer& renderer, ResourceManager& resourceManager, Scene& scene)
    {
        //imgui widgets
        renderer.AddDevWindowWidget<ImguiDragFloat3>("DC Offset", &m_DcOffset, .01f);
        renderer.AddDevWindowWidget<ImguiDragFloat3>("Amp", &m_Amp, .01f);
        renderer.AddDevWindowWidget<ImguiDragFloat3>("Freq", &m_Freq, 0.1f);
        renderer.AddDevWindowWidget<ImguiDragFloat3>("Phase", &m_Phase, 0.1f);
        // buffer and shaders setup
        m_ResourceManager->AddVertexBuffer("VBO", m_SquareVerticies, sizeof(m_SquareVerticies));
        m_ResourceManager->AddVertexArray("VAO");
        m_ResourceManager->AddIndexBuffer("IndexBuffer", m_SquareIndicies, 6);
        m_ResourceManager->AddShader("ShaderArt", m_ShaderArtVS.c_str(), m_ShaderArtFS.c_str());

        VertexBufferLayout squareLayout = {
            {ShaderDataType::Float3, "aPos"},
            {ShaderDataType::Float2, "aTexture"},
        };
        m_ResourceManager->GetVertexArray("VAO")->AddBuffer(*m_ResourceManager->GetVertexBuffer("VBO"), squareLayout);

        m_VBO = m_ResourceManager->GetVertexBuffer("VBO");
        m_VAO = m_ResourceManager->GetVertexArray("VAO");
        m_IndexBuffer = m_ResourceManager->GetIndexBuffer("IndexBuffer");
        m_Shader = m_ResourceManager->GetShader("ShaderArt");

        // ShaderArt.fs does not sample textures; it relies on uniforms like iResolution/iTime.
    }

    void TestShader::OnUpdate(float deltaTime) {}
    void TestShader::OnRender(Renderer& renderer) 
    {
        if (!m_Shader || !m_VAO || !m_IndexBuffer)
            return;

        m_Shader->Bind();

        // Required uniforms for shaders/ShaderArt.fs
        m_Shader->setVec2("iResolution", glm::vec2((float)renderer.GetWindowWidth(), (float)renderer.GetWindowHeight()));
        m_Shader->setFloat("iTime", (float)glfwGetTime());
        m_Shader->setVec3("DcOffset", m_DcOffset);
        m_Shader->setVec3("amp", m_Amp);
        m_Shader->setVec3("freq", m_Freq);
        m_Shader->setVec3("phase", m_Phase);

        m_VAO->Bind();
        m_IndexBuffer->Bind();
        glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
    }
    void TestShader::OnImGuiRender(Renderer& renderer) {}
    void TestShader::OnDetach(Renderer& renderer)
    {
        renderer.ClearDevWindowWidgets();
        m_ResourceManager->ClearVertexArrays();
        m_ResourceManager->ClearVertexBuffers();
        m_ResourceManager->ClearIndexBuffers();
        m_ResourceManager->ClearShaders();
        m_ResourceManager->ClearTextures();
        m_ResourceManager->ClearMeshes();
    }


}
