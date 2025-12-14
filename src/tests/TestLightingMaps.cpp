#include "tests/TestLightingMaps.h"

#include "Renderer.h"

namespace test {
    TestLightingMaps::TestLightingMaps(const std::string& name, ResourceManager& resourceManager, Scene& scene)
        : Test(name, resourceManager, scene), m_ResourceManager(&resourceManager) {}

    void TestLightingMaps::OnAttach(Renderer& renderer, ResourceManager& resourceManager, Scene& scene) 
    {
        renderer.EnableDepthTest(true);
        renderer.AddDevWindowWidget<ImguiDragFloat3>("Light Position", &m_LightPosition, .008f);
        renderer.AddDevWindowWidget<ImguiDragFloat3>("Rotation", &m_CubeRotation, .05f);

        m_LightingMapVS = "../shaders/LightingMaps.vs";
        m_LightingMapFS = "../shaders/LightingMaps.fs";
        m_LightCubeVS   = "../shaders/LightCubeMaps.vs";
        m_LightCubeFS   = "../shaders/LightCubeMaps.fs";

        m_ResourceManager->AddVertexBuffer("VBO", m_Verticies, sizeof(m_Verticies));
        m_ResourceManager->AddVertexArray("ObjVAO");
        
        VertexBufferLayout cubeLayout = {
            {ShaderDataType::Float3, "aPos"},
            {ShaderDataType::Float3, "aNormal"},
            {ShaderDataType::Float2, "aTexture"},
        };

        m_ResourceManager->GetVertexArray("ObjVAO")->AddBuffer(*m_ResourceManager->GetVertexBuffer("VBO"), cubeLayout);
        m_ResourceManager->AddVertexArray("LightVAO");
        m_ResourceManager->GetVertexArray("LightVAO")->AddBuffer(*m_ResourceManager->GetVertexBuffer("VBO"), cubeLayout);

        m_ResourceManager->AddShader("LightingShader", m_LightingMapVS, m_LightingMapFS);
        m_ResourceManager->AddShader("LightCubeShader", m_LightCubeVS, m_LightCubeFS);
    
        m_ResourceManager->AddTexture("ContainerDiffuse", "../res/crate.png", true, true);
        m_ResourceManager->AddTexture("ContainerSpecular", "../res/crate_specular.png", true, true);
        
        m_ResourceManager->AddMesh("Cube", Mesh::CreateCube(CubeFeature::Position | CubeFeature::Normal | CubeFeature::TexCoord));
        m_ResourceManager->AddMesh("LightCube", Mesh::CreateCube(CubeFeature::Position));

        m_VBO = m_ResourceManager->GetVertexBuffer("VBO");
        m_ObjVAO = m_ResourceManager->GetVertexArray("ObjVAO");
        m_LightVAO = m_ResourceManager->GetVertexArray("LightVAO");
        m_LightingShader = m_ResourceManager->GetShader("LightingShader");
        m_LightCubeShader = m_ResourceManager->GetShader("LightCubeShader");
        m_DiffuseMap = m_ResourceManager->GetTexture("ContainerDiffuse");
        m_SpecularMap = m_ResourceManager->GetTexture("ContainerSpecular");
        m_CubeMesh = m_ResourceManager->GetMesh("Cube");
        m_LightCubeMesh = m_ResourceManager->GetMesh("LightCube");

        if(m_LightingShader)
        {
            m_LightingShader->Bind();
            m_LightingShader->setInt("material.diffuse", 0);
            m_LightingShader->setInt("material.specular", 1);
        }
    }
    void TestLightingMaps::OnUpdate(float deltaTime) {}
    void TestLightingMaps::OnRender(Renderer& renderer) 
    {
        renderer.SetClearColor(0.1f, 0.1f, 0.1f);
        m_LightingShader->Bind();
        m_DiffuseMap->BindandActivate(GL_TEXTURE0);
        m_SpecularMap->BindandActivate(GL_TEXTURE1);

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
        m_CubeMesh->Draw(renderer, view, projection);
        m_ObjVAO->Unbind();
    
        m_LightCubeShader->Bind();
        m_LightCubeShader->setMat4("projection", projection);
        m_LightCubeShader->setMat4("view", view);
        
        model = glm::mat4(1.f);
        model = glm::translate(model, m_LightPosition);
        model = glm::scale(model, glm::vec3(0.2f));
        m_LightCubeShader->setMat4("model", model);

        m_LightVAO->Bind();
        m_LightCubeMesh->Draw(renderer, view, projection);
    }
    void TestLightingMaps::OnImGuiRender(Renderer& renderer) {}
    void TestLightingMaps::OnDetach(Renderer& renderer) 
    {
        renderer.EnableDepthTest(false);
        renderer.SetClearColor(renderer.GetWindowDefaultColor());
        m_ResourceManager->ClearTextures();    
        m_ResourceManager->ClearVertexArrays();
        m_ResourceManager->ClearVertexBuffers();
        m_ResourceManager->ClearShaders();
        m_ResourceManager->ClearMeshes();
}

}
