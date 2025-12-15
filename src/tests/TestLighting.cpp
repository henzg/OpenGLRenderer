#include "tests/TestLighting.h"

#include "ImguiWidget.h"
#include "Renderer.h"


namespace test 
{
    TestLighting::TestLighting(const std::string& name, ResourceManager& resourceManager, Scene& scene)
        : Test(name, resourceManager, scene), m_ResourceManager(&resourceManager) {}

    TestLighting::~TestLighting() {}

    
void TestLighting::OnAttach(Renderer& renderer, ResourceManager& resourceManager, Scene& scene)
        {

            renderer.EnableDepthTest(true);

            renderer.AddDevWindowWidget<ImguiDragFloat3>("Light Pos", &m_LightPosition, .05);
            renderer.AddDevWindowWidget<ImguiSliderFloat>("Specular", &m_SpecModify, .0f, 1.0f);
            renderer.AddDevWindowWidget<ImguiSliderFloat>("Ambient", &m_AmbientModify, .0f, 1.f);
            renderer.AddDevWindowWidget<ImguiSliderFloat>("Diffuse", &m_DiffuseModify, .0f, 1.0f);
            
            m_ResourceManager->AddShader("LightingShader", m_LightingColorVS.c_str(), m_LightingColorFS.c_str());
            m_ResourceManager->AddShader("LightCubeShader", m_LightCubeVS.c_str(), m_LightCubeFS.c_str());
            m_LightingShader = m_ResourceManager->GetShader("LightingShader");
            m_LightCubeShader = m_ResourceManager->GetShader("LightCubeShader");

            // Create meshes (previously null -> crash in OnRender)
            m_ResourceManager->AddMesh("LightingCube", Mesh::CreateCube(CubeFeature::Position | CubeFeature::Normal));
            m_ResourceManager->AddMesh("LightingLightCube", Mesh::CreateCube(CubeFeature::Position));
            m_CubeMesh = m_ResourceManager->GetMesh("LightingCube");
            m_LightCubeMesh = m_ResourceManager->GetMesh("LightingLightCube");

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
            cube.bind = [this](Shader& shader, const Renderer& r) {
                shader.setVec3("objectColor", m_ObjectColor);
                shader.setVec3("lightColor", m_LightColor);
                shader.setVec3("lightPos", m_LightPosition);
                shader.setVec3("viewPos", r.GetCameraPosition());
                shader.setFloat("specModify", m_SpecModify);
                shader.setFloat("ambientModify", m_AmbientModify);
                shader.setFloat("diffuseModify", m_DiffuseModify);
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

        void TestLighting::OnUpdate(float deltaTime) {}
        void TestLighting::OnRender(Renderer& renderer) 
        {
            // Draw is handled by Scene::Entity in Renderer::OnRender(scene)
        }
        void TestLighting::OnImGuiRender(Renderer& renderer) {}
        void TestLighting::OnDetach(Renderer& renderer) 
        {
            // Central cleanup happens on test switch/back.
            m_LightingShader = nullptr;
            m_LightCubeShader = nullptr;
            m_CubeMesh = nullptr;
            m_LightCubeMesh = nullptr;
        }

}
