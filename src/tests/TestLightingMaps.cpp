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

        m_ResourceManager->AddShader("LightingShader", m_LightingMapVS, m_LightingMapFS);
        m_ResourceManager->AddShader("LightCubeShader", m_LightCubeVS, m_LightCubeFS);
    
        m_ResourceManager->AddTexture("ContainerDiffuse", "../res/crate.png", true, true);
        m_ResourceManager->AddTexture("ContainerSpecular", "../res/crate_specular.png", true, true);
        
        m_ResourceManager->AddMesh("Cube", Mesh::CreateCube(CubeFeature::Position | CubeFeature::Normal | CubeFeature::TexCoord));
        m_ResourceManager->AddMesh("LightCube", Mesh::CreateCube(CubeFeature::Position));
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

        // Option B: Entities (projection/view/model handled by renderer)
        Scene::Entity cube{};
        cube.mesh = m_CubeMesh;
        cube.shader = m_LightingShader;
        cube.update = [this](Scene::Transform& t, const Renderer&) {
            t.rotationDeg = m_CubeRotation;
        };
        cube.bind = [this](Shader& shader, const Renderer& r) {
            if (m_DiffuseMap) m_DiffuseMap->BindandActivate(GL_TEXTURE0);
            if (m_SpecularMap) m_SpecularMap->BindandActivate(GL_TEXTURE1);

            shader.setVec3("light.ambient", m_LightAmbient);
            shader.setVec3("light.diffuse", m_LightDiffuse);
            shader.setVec3("light.specular", m_LightSpecular);
            shader.setVec3("light.position", m_LightPosition);
            shader.setVec3("viewPos", r.GetCameraPosition());
            shader.setFloat("material.shininess", 64.f);
        };
        scene.AddEntity(cube);

        Scene::Entity light{};
        light.mesh = m_LightCubeMesh;
        light.shader = m_LightCubeShader;
        light.update = [this](Scene::Transform& t, const Renderer&) {
            t.position = m_LightPosition;
            t.scale = glm::vec3(0.2f);
        };
        scene.AddEntity(light);
    }
    void TestLightingMaps::OnUpdate(float deltaTime) {}
    void TestLightingMaps::OnRender(Renderer& renderer) 
    {
        renderer.SetClearColor(0.1f, 0.1f, 0.1f);
        // Draw is handled by Scene::Entity in Renderer::OnRender(scene)
    }
    void TestLightingMaps::OnImGuiRender(Renderer& renderer) {}
    void TestLightingMaps::OnDetach(Renderer& renderer) 
    {
        // Central cleanup happens on test switch/back.
        m_LightingShader = nullptr;
        m_LightCubeShader = nullptr;
        m_DiffuseMap = nullptr;
        m_SpecularMap = nullptr;
        m_CubeMesh = nullptr;
        m_LightCubeMesh = nullptr;
}

}
