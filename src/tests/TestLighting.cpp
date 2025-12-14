#include "tests/TestLighting.h"

#include "ImguiWidget.h"
#include "VertexBufferLayout.h"
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

            m_ResourceManager->AddVertexArray("ObjVAO");
            m_ResourceManager->AddVertexBuffer("ObjVBO", m_Verticies, sizeof(m_Verticies));
            VertexBufferLayout cubeLayout = {
                {ShaderDataType::Float3, "aPos"},
                {ShaderDataType::Float3, "aNormal"},
            };
            m_ResourceManager->GetVertexArray("ObjVAO")->AddBuffer(*m_ResourceManager->GetVertexBuffer("ObjVBO"), cubeLayout);
            
            m_ResourceManager->AddVertexArray("LightVAO");
            m_ResourceManager->GetVertexArray("LightVAO")->AddBuffer(*m_ResourceManager->GetVertexBuffer("ObjVBO"), cubeLayout);
            
            m_ResourceManager->AddShader("LightingShader", m_LightingColorVS.c_str(), m_LightingColorFS.c_str());
            m_ResourceManager->AddShader("LightCubeShader", m_LightCubeVS.c_str(), m_LightCubeFS.c_str());

            m_ObjVAO = m_ResourceManager->GetVertexArray("ObjVAO");
            m_LightVAO = m_ResourceManager->GetVertexArray("LightVAO");
            m_VBO = m_ResourceManager->GetVertexBuffer("ObjVBO");
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

        }

        void TestLighting::OnUpdate(float deltaTime) {}
        void TestLighting::OnRender(Renderer& renderer) 
        {
            m_LightingShader->Bind();
            m_LightingShader->setVec3("objectColor", m_ObjectColor);
            m_LightingShader->setVec3("lightColor", m_LightColor);
            m_LightingShader->setVec3("lightPos", m_LightPosition);
            m_LightingShader->setVec3("viewPos", renderer.GetCameraPosition());
            m_LightingShader->setFloat("specModify", m_SpecModify);
            m_LightingShader->setFloat("ambientModify", m_AmbientModify);
            m_LightingShader->setFloat("diffuseModify", m_DiffuseModify);
    
            glm::mat4 projection = glm::perspective(glm::radians(renderer.GetCameraZoom()), 
                                    (float)renderer.GetWindowWidth() / (float)renderer.GetWindowHeight(), 0.1f, 100.f);
            glm::mat4 view = renderer.GetCameraViewMatrix();
            m_LightingShader->setMat4("projection", projection);
            m_LightingShader->setMat4("view", view);

            glm::mat4 model = glm::mat4(1.f);
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
        void TestLighting::OnImGuiRender(Renderer& renderer) {}
        void TestLighting::OnDetach(Renderer& renderer) 
        {
            renderer.ClearDevWindowWidgets();
            renderer.EnableDepthTest(false);
            m_ResourceManager->ClearVertexArrays();
            m_ResourceManager->ClearVertexBuffers();
            m_ResourceManager->ClearShaders();
            m_ResourceManager->ClearTextures();
            m_ResourceManager->ClearMeshes();
        }

}
