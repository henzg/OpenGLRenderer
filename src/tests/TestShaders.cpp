#include "tests/TestShaders.h"
#include "ImguiWidget.h"
#include "Renderer.h"

namespace test
{
    TestShader::TestShader(const std::string& name)
        : Test(name) {}
    TestShader::~TestShader() {}

    void TestShader::OnAttach(Renderer& renderer)
    {
        //imgui widgets
        renderer.AddDevWindowWidget<ImguiDragFloat3>("DC Offset", &m_DcOffset, .01f);
        renderer.AddDevWindowWidget<ImguiDragFloat3>("Amp", &m_Amp, .01f);
        renderer.AddDevWindowWidget<ImguiDragFloat3>("Freq", &m_Freq, 0.1f);
        renderer.AddDevWindowWidget<ImguiDragFloat3>("Phase", &m_Phase, 0.1f);
        // buffer and shaders setup
        m_VBO = std::make_unique<VertexBuffer>(m_SquareVerticies, sizeof(m_SquareVerticies));
        m_VAO = std::make_unique<VertexArray>();
        m_IndexBuffer = std::make_unique<IndexBuffer>(m_SquareIndicies, 6);
        m_Shader = std::make_unique<Shader>(m_ShaderArtVS.c_str(), m_ShaderArtFS.c_str());
       VertexBufferLayout squareLayout = {
            {ShaderDataType::Float3, "aPos"},
            {ShaderDataType::Float2, "aTexture"},
        };
        m_VAO->AddBuffer(*m_VBO, squareLayout);
        m_VAO->Unbind();
    }

    void TestShader::OnUpdate(float deltaTime) {}
    void TestShader::OnRender(Renderer& renderer) 
    {
        m_VAO->Bind();
        m_IndexBuffer->Bind();
        m_Shader->Bind();
        glm::vec2 iResolution(renderer.GetWindowWidth(), renderer.GetWindowHeight());
        m_Shader->setFloat("iTime", static_cast<float>(glfwGetTime()));
        m_Shader->setVec2("iResolution", iResolution);
        m_Shader->setVec3("DcOffset", m_DcOffset);
        m_Shader->setVec3("amp", m_Amp);
        m_Shader->setVec3("freq", m_Freq);
        m_Shader->setVec3("phase", m_Phase);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
    void TestShader::OnImGuiRender(Renderer& renderer) {}
    void TestShader::OnDetach(Renderer& renderer) {}


}
