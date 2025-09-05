#pragma once

#include "tests/Test.h"
#include "Mesh.h"
#include "Materials.h"

namespace test
{

    class TestMaterials : public Test
    {
    private:
        std::unique_ptr<VertexArray> m_ObjVAO;
        std::unique_ptr<VertexArray> m_LightVAO;
        std::unique_ptr<VertexBuffer> m_VBO;
        std::unique_ptr<Shader> m_LightingShader;
        std::unique_ptr<Shader> m_LightCubeShader;

        std::string m_LightingColorVS = "../shaders/MaterialLighting.vs";
        std::string m_LightingColorFS = "../shaders/MaterialLighting.fs";
        std::string m_LightCubeVS = "../shaders/MaterialCoreLight.vs";
        std::string m_LightCubeFS = "../shaders/MaterialCoreLight.fs";

        glm::vec3 m_LightAmbient =  glm::vec3(1.f);
        glm::vec3 m_LightDiffuse =  glm::vec3(1.f);
        glm::vec3 m_LightSpecular = glm::vec3(1.f);
        glm::vec3 m_LightPosition = {1.2f, 1.0f, 2.0f};
        float m_Verticies[6*36] = 
        {
            // pos[0:2] normal[3:5]
            -0.5f, -0.5f, -0.5f, 0.f, 0.f, -1.f, 
             0.5f, -0.5f, -0.5f, 0.f, 0.f, -1.f, 
             0.5f,  0.5f, -0.5f, 0.f, 0.f, -1.f, 
             0.5f,  0.5f, -0.5f, 0.f, 0.f, -1.f,
            -0.5f,  0.5f, -0.5f, 0.f, 0.f, -1.f,
            -0.5f, -0.5f, -0.5f, 0.f, 0.f, -1.f,

            -0.5f, -0.5f,  0.5f,  0.f, 0.f, 1.f, 
             0.5f, -0.5f,  0.5f,  0.f, 0.f, 1.f,
             0.5f,  0.5f,  0.5f,  0.f, 0.f, 1.f, 
             0.5f,  0.5f,  0.5f,  0.f, 0.f, 1.f,
            -0.5f,  0.5f,  0.5f,  0.f, 0.f, 1.f,
            -0.5f, -0.5f,  0.5f,  0.f, 0.f, 1.f,

            -0.5f,  0.5f,  0.5f, -1.f, 0.f, 0.f, 
            -0.5f,  0.5f, -0.5f, -1.f, 0.f, 0.f,
            -0.5f, -0.5f, -0.5f, -1.f, 0.f, 0.f,
            -0.5f, -0.5f, -0.5f, -1.f, 0.f, 0.f,
            -0.5f, -0.5f,  0.5f, -1.f, 0.f, 0.f,
            -0.5f,  0.5f,  0.5f, -1.f, 0.f, 0.f,

             0.5f,  0.5f,  0.5f,  1.f, 0.f, 0.f,   
             0.5f,  0.5f, -0.5f,  1.f, 0.f, 0.f, 
             0.5f, -0.5f, -0.5f,  1.f, 0.f, 0.f, 
             0.5f, -0.5f, -0.5f,  1.f, 0.f, 0.f, 
             0.5f, -0.5f,  0.5f,  1.f, 0.f, 0.f, 
             0.5f,  0.5f,  0.5f,  1.f, 0.f, 0.f, 

            -0.5f, -0.5f, -0.5f,  0.f,-1.f, 0.f, 
             0.5f, -0.5f, -0.5f,  0.f,-1.f, 0.f, 
             0.5f, -0.5f,  0.5f,  0.f,-1.f, 0.f, 
             0.5f, -0.5f,  0.5f,  0.f,-1.f, 0.f, 
            -0.5f, -0.5f,  0.5f,  0.f,-1.f, 0.f, 
            -0.5f, -0.5f, -0.5f,  0.f,-1.f, 0.f, 

            -0.5f,  0.5f, -0.5f,  0.f, 1.f, 0.f, 
             0.5f,  0.5f, -0.5f,  0.f, 1.f, 0.f, 
             0.5f,  0.5f,  0.5f,  0.f, 1.f, 0.f, 
             0.5f,  0.5f,  0.5f,  0.f, 1.f, 0.f, 
            -0.5f,  0.5f,  0.5f,  0.f, 1.f, 0.f,
            -0.5f,  0.5f, -0.5f,  0.f, 1.f, 0.f
        };

        Material m_CurrentMaterial;
        MaterialName m_SelectedMaterial = MaterialName::EMERALD;
        static const char* GetMaterialNameString(MaterialName material);
        static MaterialName GetMaterialNameFromIndex(int index);
        static int GetMaterialCount();

    public:
        TestMaterials(const std::string& name);
        ~TestMaterials();

        void OnAttach(Renderer& renderer) override;
        void OnUpdate(float deltaTime) override;
        void OnRender(Renderer& renderer) override;
        void OnImGuiRender(Renderer& renderer) override;
        void OnDetach(Renderer& renderer) override;
    };



}
