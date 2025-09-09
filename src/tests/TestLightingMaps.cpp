#include "tests/TestLightingMaps.h"

#include "Renderer.h"

namespace test {
    TestLightingMaps::TestLightingMaps(const std::string& name) 
        : Test(name) {}

    void TestLightingMaps::OnAttach(Renderer& renderer) 
    {
        glEnable(GL_DEPTH_TEST);

        renderer.AddDevWindowWidget<ImguiDragFloat3>("Light Position", &m_LightPosition, .008);
        std::string m_LightingMapVS = "../shaders/LightingMaps.vs";
        std::string m_LightingMapFS = "../shaders/LightingMaps.fs";
        std::string m_LightCubeVS   = "../shaders/LightCubeMaps.vs";
        std::string m_LightCubeFS   = "../shaders/LightCubeMaps.fs";

        m_VBO = std::make_unique<VertexBuffer>(m_Verticies, sizeof(m_Verticies));
        m_ObjVAO = std::make_unique<VertexArray>();
        
        VertexBufferLayout cubeLayout = {
            {ShaderDataType::Float3, "aPos"},
            {ShaderDataType::Float3, "aNormal"},
            {ShaderDataType::Float2, "aTexture"},
        };

        m_ObjVAO->AddBuffer(*m_VBO, cubeLayout);
        m_ObjVAO->Unbind();

        m_LightVAO = std::make_unique<VertexArray>();
        m_LightVAO->AddBuffer(*m_VBO, cubeLayout);
        m_LightVAO->Unbind();

        m_LightingShader = std::make_unique<Shader>(m_LightingMapVS.c_str(), m_LightingMapFS.c_str());
        m_LightCubeShader = std::make_unique<Shader>(m_LightCubeVS.c_str(), m_LightCubeFS.c_str());
    
        m_LightingShader->Bind();
        renderer.AddTexture("crate", "../res/crate.png", true, true);
        m_LightingShader->setInt("material.diffuse", 0);
        m_LightingShader->Unbind();
    }
    void TestLightingMaps::OnUpdate(float deltaTime) {}
    void TestLightingMaps::OnRender(Renderer& renderer) 
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        m_LightingShader->Bind();
        Texture* tex1 = renderer.GetTexture("crate");
        if (tex1) tex1->BindandActivate(GL_TEXTURE0);

        m_LightingShader->setVec3("light.ambient", m_LightAmbient);
        m_LightingShader->setVec3("light.diffuse", m_LightDiffuse);
        m_LightingShader->setVec3("light.specular", m_LightSpecular);
        m_LightingShader->setVec3("light.position", m_LightPosition);
        m_LightingShader->setVec3("viewPos", renderer.GetCameraPosition());
        m_LightingShader->setVec3("material.specular", {0.5,0.5,0.5});
        m_LightingShader->setFloat("material.shininess", 64.f);
        
        glm::mat4 projection = glm::perspective(glm::radians(renderer.GetCameraZoom()), 
                            (float)renderer.GetWindowWidth() / (float)renderer.GetWindowHeight(), 0.1f, 100.f);
        glm::mat4 view = renderer.GetCameraViewMatrix();
        glm::mat4 model = glm::mat4(1.f);
        m_LightingShader->setMat4("projection", projection);
        m_LightingShader->setMat4("view", view);
        m_LightingShader->setMat4("model", model);

        m_ObjVAO->Bind();
        glDrawArrays(GL_TRIANGLES, 0, 36);
        m_ObjVAO->Unbind();
    
        m_LightCubeShader->Bind();
        m_LightCubeShader->setMat4("projection", projection);
        m_LightCubeShader->setMat4("view", view);
        
        model = glm::mat4(1.f);
        model = glm::translate(model, m_LightPosition);
        model = glm::scale(model, glm::vec3(0.2f));
        m_LightCubeShader->setMat4("model", model);

        m_LightVAO->Bind();
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    void TestLightingMaps::OnImGuiRender(Renderer& renderer) {}
    void TestLightingMaps::OnDetach(Renderer& renderer) 
    {
        glDisable(GL_DEPTH_TEST);
        renderer.ClearTextures();
    }

}
