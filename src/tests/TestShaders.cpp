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
        // mesh and shaders setup
        VertexBufferLayout squareLayout = {
            {ShaderDataType::Float3, "aPos"},
            {ShaderDataType::Float2, "aTexture"},
        };

        m_ResourceManager->AddMesh("ShaderArtQuad", m_SquareVerticies, 4, m_SquareIndicies, 6, squareLayout);
        m_ResourceManager->AddShader("ShaderArt", m_ShaderArtVS.c_str(), m_ShaderArtFS.c_str());

        m_Mesh = m_ResourceManager->GetMesh("ShaderArtQuad");
        m_Shader = m_ResourceManager->GetShader("ShaderArt");

        // ShaderArt.fs does not sample textures; it relies on uniforms like iResolution/iTime.

        Scene::Entity e{};
        e.mesh = m_Mesh;
        e.shader = m_Shader;
        e.bind = [this](Shader& shader, const Renderer& r) {
            shader.setVec2("iResolution", glm::vec2((float)r.GetWindowWidth(), (float)r.GetWindowHeight()));
            shader.setFloat("iTime", (float)glfwGetTime());
            shader.setVec3("DcOffset", m_DcOffset);
            shader.setVec3("amp", m_Amp);
            shader.setVec3("freq", m_Freq);
            shader.setVec3("phase", m_Phase);
        };
        scene.AddEntity(e);
    }

    void TestShader::OnUpdate(float deltaTime) {}
    void TestShader::OnRender(Renderer& renderer) 
    {
        // Draw is handled by Scene::Entity in Renderer::OnRender(scene)
    }
    void TestShader::OnImGuiRender(Renderer& renderer) {}
    void TestShader::OnDetach(Renderer& renderer)
    {
        m_Mesh = nullptr;
        m_Shader = nullptr;
    }


}
