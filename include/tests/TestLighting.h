#pragma once

#include "glm/fwd.hpp"
#include "tests/Test.h"
#include "glm/glm.hpp"
#include <memory>

#include "Shader.h"

namespace test
{
    class TestLighting : public Test
    {
    private:
        ResourceManager* m_ResourceManager = nullptr;
        Shader* m_LightingShader = nullptr;
        Shader* m_LightCubeShader = nullptr;
        const Mesh* m_CubeMesh = nullptr;
        const Mesh* m_LightCubeMesh = nullptr;

        std::string m_LightingColorVS = "../shaders/Lighting.vs";
        std::string m_LightingColorFS = "../shaders/Lighting.fs";
        std::string m_LightCubeVS = "../shaders/CoreLight.vs";
        std::string m_LightCubeFS = "../shaders/CoreLight.fs";

        glm::vec3 m_ObjectColor = {1.f, .5f, .31f};
        glm::vec3 m_LightColor = {1.f, 1.f, 1.f};
        float m_SpecModify = 0.0f;
        float m_AmbientModify = 0.0f;
        float m_DiffuseModify = 0.0f;
        bool m_DisableLighting = false;

        glm::vec3 m_LightPosition = {1.2f, 1.0f, 2.0f};
    public:
        TestLighting(const std::string& name, ResourceManager& resourceManager, Scene& scene);
        ~TestLighting();

        void OnAttach(Renderer& renderer, ResourceManager& resourceManager, Scene& scene) override;
        void OnUpdate(float deltaTime) override;
        void OnRender(Renderer& renderer) override;
        void OnImGuiRender(Renderer& renderer) override;
        void OnDetach(Renderer& renderer) override;
        
    };
}
