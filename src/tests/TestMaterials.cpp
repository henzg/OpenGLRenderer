#include "tests/TestMaterials.h"
#include "VertexBufferLayout.h"

#include "Renderer.h"
#include "imgui/imgui.h"

namespace test
{

        TestMaterials::TestMaterials(const std::string& name, ResourceManager& resourceManager, Scene& scene)
        : Test(name, resourceManager, scene), m_ResourceManager(&resourceManager) {}
        TestMaterials::~TestMaterials() {}

        void TestMaterials::OnAttach(Renderer& renderer, ResourceManager& resourceManager, Scene& scene) 
        {
            renderer.EnableDepthTest(true);
            renderer.AddDevWindowWidget<ImguiDragFloat3>("Light Position", &m_LightPosition, .02);
            m_CurrentMaterial.setMaterial(m_SelectedMaterial);
            
            m_ResourceManager->AddVertexArray("ObjVAO");
            m_ResourceManager->AddVertexBuffer("VBO", m_Verticies, sizeof(m_Verticies));
            VertexBufferLayout cubeLayout =
            {
                {ShaderDataType::Float3, "aPos"},
                {ShaderDataType::Float3, "aNormal"},
            };
            
            m_ResourceManager->GetVertexArray("ObjVAO")->AddBuffer(*m_ResourceManager->GetVertexBuffer("VBO"), cubeLayout);
            m_ResourceManager->AddVertexArray("LightVAO");
            m_ResourceManager->GetVertexArray("LightVAO")->AddBuffer(*m_ResourceManager->GetVertexBuffer("VBO"), cubeLayout);

            m_ResourceManager->AddShader("MaterialLightingShader", m_LightingColorVS.c_str(), m_LightingColorFS.c_str());
            m_ResourceManager->AddShader("CoreLightShader", m_LightCubeVS.c_str(), m_LightCubeFS.c_str());

            m_ResourceManager->AddMesh("Cube", Mesh::CreateCube(CubeFeature::Position | CubeFeature::Normal));
            m_ResourceManager->AddMesh("LightCube", Mesh::CreateCube(CubeFeature::Position));

            m_ObjVAO = m_ResourceManager->GetVertexArray("ObjVAO");
            m_LightVAO = m_ResourceManager->GetVertexArray("LightVAO");
            m_VBO = m_ResourceManager->GetVertexBuffer("VBO");
            m_LightingShader = m_ResourceManager->GetShader("MaterialLightingShader");
            m_LightCubeShader = m_ResourceManager->GetShader("CoreLightShader");
            m_CubeMesh = m_ResourceManager->GetMesh("Cube");
            m_LightCubeMesh = m_ResourceManager->GetMesh("LightCube");

            if (m_LightingShader)
            {
                m_LightingShader->Bind();
                m_LightingShader->setInt("material.diffuse", 0);
                m_LightingShader->setInt("material.specular", 1);
            }

        }

        void TestMaterials::OnUpdate(float deltaTime) {}

        void TestMaterials::OnRender(Renderer& renderer) 
        {

            const auto& mat = m_CurrentMaterial.getMaterialElement();
            m_LightingShader->Bind();
            m_LightingShader->setVec3("light.ambient", m_LightAmbient);
            m_LightingShader->setVec3("light.diffuse", m_LightDiffuse);
            m_LightingShader->setVec3("light.specular", m_LightSpecular);
            m_LightingShader->setVec3("light.position", m_LightPosition);
            m_LightingShader->setVec3("viewPos", renderer.GetCameraPosition());
            m_LightingShader->setVec3("material.ambient", mat.ambient);
            m_LightingShader->setVec3("material.diffuse", mat.diffuse);
            m_LightingShader->setVec3("material.specular", mat.specular);
            m_LightingShader->setFloat("material.shininess", mat.shininess);
                        

            glm::mat4 projection = glm::perspective(glm::radians(renderer.GetCameraZoom()), 
                                (float)renderer.GetWindowWidth() / (float)renderer.GetWindowHeight(), 0.1f, 100.f);
            glm::mat4 view = renderer.GetCameraViewMatrix();
            glm::mat4 model = glm::mat4(1.f);
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
        void TestMaterials::OnImGuiRender(Renderer& renderer) 
        {
            int currentIdx = static_cast<int>(m_SelectedMaterial);
            const char* preview = GetMaterialNameString(m_SelectedMaterial);

            if(ImGui::BeginCombo("Material", preview))
            {
                for (int i = 0; i < GetMaterialCount(); i++)
                {
                    MaterialName material = GetMaterialNameFromIndex(i);
                    const char* materialName = GetMaterialNameString(material);
                    bool isSelected = (currentIdx == i);

                    if(ImGui::Selectable(materialName, isSelected))
                    {
                        m_SelectedMaterial = material;
                        m_CurrentMaterial.setMaterial(m_SelectedMaterial);
                    }
                    
                    if(isSelected)
                    {
                        ImGui::SetItemDefaultFocus();
                    }
                }
                ImGui::EndCombo();
            }

            if (ImGui::CollapsingHeader("Material Properties"))
            {
                const auto& mat = m_CurrentMaterial.getMaterialElement();
                ImGui::Text("Ambient: %.3f, %.3f, %.3f", mat.ambient.x, mat.ambient.y, mat.ambient.z);
                ImGui::Text("Diffuse: %.3f, %.3f, %.3f", mat.diffuse.x, mat.diffuse.y, mat.diffuse.z);
                ImGui::Text("Specular: %.3f, %.3f, %.3f", mat.specular.x, mat.specular.y, mat.specular.z);
                ImGui::Text("Shininess: %.1f", mat.shininess);
            }
            
        }
        
        void TestMaterials::OnDetach(Renderer& renderer) 
        {
            renderer.EnableDepthTest(false);
            m_ResourceManager->ClearVertexArrays();
            m_ResourceManager->ClearVertexBuffers();
            m_ResourceManager->ClearShaders();
            m_ResourceManager->ClearMeshes();
        }

        const char* TestMaterials::GetMaterialNameString(MaterialName material)
        {
            switch(material)
            {
                case MaterialName::NONE: return "None";
                case MaterialName::EMERALD: return "Emerald";
                case MaterialName::JADE: return "Jade";
                case MaterialName::OBSIDIAN: return "Obsidian";
                case MaterialName::PEARL: return "Pearl";
                case MaterialName::RUBY: return "Ruby";
                case MaterialName::TURQUOISE: return "Turquoise";
                case MaterialName::BRASS: return "Brass";
                case MaterialName::BRONZE: return "Bronze";
                case MaterialName::CHROME: return "Chrome";
                default: return "Unknown";
            }
        }

        MaterialName TestMaterials::GetMaterialNameFromIndex(int index)
        {
            return static_cast<MaterialName>(index);
        }

        int TestMaterials::GetMaterialCount()
        {
            return static_cast<int>(MaterialName::CHROME) + 1;
        }

}
