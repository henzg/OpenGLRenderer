#include "tests/TestLightingMaps.h"

#include "Renderer.h"

namespace test {
    TestLightingMaps::TestLightingMaps(const std::string& name) 
        : Test(name) {}

    void TestLightingMaps::OnAttach(Renderer& renderer) 
    {
        renderer.EnableDepthTest(true);
        renderer.AddDevWindowWidget<ImguiDragFloat3>("Light Position", &m_LightPosition, .008f);
        renderer.AddDevWindowWidget<ImguiDragFloat3>("Rotation", &m_CubeRotation, .05f);
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
        renderer.AddTexture("crateSpec", "../res/crate_specular.png", true, true);
        renderer.AddTexture("theMatrix", "../res/matrix.jpg", false, true);
        renderer.AddTexture("coloredSpec", "../res/container2_specular_colored.png", true, true);
        m_LightingShader->setInt("material.diffuse", 0);
        m_LightingShader->setInt("material.specular", 1);
        m_LightingShader->Unbind();
    }
    void TestLightingMaps::OnUpdate(float deltaTime) {}
    void TestLightingMaps::OnRender(Renderer& renderer) 
    {
        renderer.SetClearColor(0.1f, 0.1f, 0.1f);
        m_LightingShader->Bind();
        Texture* tex1 = renderer.GetTexture("crate");
        Texture* tex2 = renderer.GetTexture("crateSpec");
        Texture* tex3 = renderer.GetTexture("theMatrix");
        if (tex1) tex1->BindandActivate(GL_TEXTURE0);
        if (tex2) tex2->BindandActivate(GL_TEXTURE1);
        if (tex3) tex3->BindandActivate(GL_TEXTURE2);

        m_LightingShader->setVec3("light.ambient", m_LightAmbient);
        m_LightingShader->setVec3("light.diffuse", m_LightDiffuse);
        m_LightingShader->setVec3("light.specular", m_LightSpecular);
        m_LightingShader->setVec3("light.position", m_LightPosition);
        m_LightingShader->setVec3("viewPos", renderer.GetCameraPosition());
        m_LightingShader->setFloat("material.shininess", 64.f);
        
        glm::mat4 projection = glm::perspective(glm::radians(renderer.GetCameraZoom()), 
                            (float)renderer.GetWindowWidth() / (float)renderer.GetWindowHeight(), 0.1f, 100.f);
        glm::mat4 view = renderer.GetCameraViewMatrix();
        glm::mat4 model = glm::mat4(1.f);
        model = glm::rotate(model, glm::radians(m_CubeRotation[0]), glm::vec3(1.f, 0.f, .0f));
        model = glm::rotate(model, glm::radians(m_CubeRotation[1]), glm::vec3(0.f, 1.f, .0f));
        model = glm::rotate(model, glm::radians(m_CubeRotation[2]), glm::vec3(0.f, 0.f, 1.f));
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
        renderer.EnableDepthTest(false);
        renderer.SetClearColor(renderer.GetWindowDefaultColor());
        renderer.ClearTextures();    
        renderer.ClearTextures();
}

}
