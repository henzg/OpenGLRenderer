#include "tests/TestMaterials.h"

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
            
            m_ResourceManager->AddShader("MaterialLightingShader", m_LightingColorVS.c_str(), m_LightingColorFS.c_str());
            m_ResourceManager->AddShader("CoreLightShader", m_LightCubeVS.c_str(), m_LightCubeFS.c_str());

            m_ResourceManager->AddMesh("Cube", Mesh::CreateCube(CubeFeature::Position | CubeFeature::Normal));
            m_ResourceManager->AddMesh("LightCube", Mesh::CreateCube(CubeFeature::Position));
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

            // Option B: Entities (projection/view/model handled by renderer)
            Scene::Entity cube{};
            cube.mesh = m_CubeMesh;
            cube.shader = m_LightingShader;
            cube.bind = [this](Shader& shader, const Renderer& r) {
                const auto& mat = m_CurrentMaterial.getMaterialElement();
                shader.setVec3("light.ambient", m_LightAmbient);
                shader.setVec3("light.diffuse", m_LightDiffuse);
                shader.setVec3("light.specular", m_LightSpecular);
                shader.setVec3("light.position", m_LightPosition);
                shader.setVec3("viewPos", r.GetCameraPosition());
                shader.setVec3("material.ambient", mat.ambient);
                shader.setVec3("material.diffuse", mat.diffuse);
                shader.setVec3("material.specular", mat.specular);
                shader.setFloat("material.shininess", mat.shininess);
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

        void TestMaterials::OnUpdate(float deltaTime) {}

        void TestMaterials::OnRender(Renderer& renderer) 
        {
            // Draw is handled by Scene::Entity in Renderer::OnRender(scene)
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
            // Central cleanup happens on test switch/back.
            m_LightingShader = nullptr;
            m_LightCubeShader = nullptr;
            m_CubeMesh = nullptr;
            m_LightCubeMesh = nullptr;
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
