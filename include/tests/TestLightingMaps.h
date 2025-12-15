#pragma once
#include "tests/Test.h"
#include "Shader.h"
#include "Texture.h"

#include <memory>


namespace test {
    class TestLightingMaps : public Test {
private:
    ResourceManager* m_ResourceManager = nullptr;
    Shader* m_LightingShader = nullptr;
    Shader* m_LightCubeShader = nullptr;
    Texture* m_DiffuseMap = nullptr;
    Texture* m_SpecularMap = nullptr;
    const Mesh* m_CubeMesh = nullptr;
    const Mesh* m_LightCubeMesh = nullptr;
    
    std::string m_LightingMapVS;
    std::string m_LightingMapFS;
    std::string m_LightCubeVS;
    std::string m_LightCubeFS;
    
    glm::vec3 m_LightAmbient = glm::vec3(1.f);
    glm::vec3 m_LightDiffuse = glm::vec3(1.f);
    glm::vec3 m_LightSpecular = glm::vec3(1.f);
    glm::vec3 m_LightPosition = {1.2f, 1.f, 2.f};
    glm::vec3 m_CubeRotation = {.0f, .0f, .0f};

public:
    TestLightingMaps(const std::string& name, ResourceManager& resourceManager, Scene& scene);
    ~TestLightingMaps() = default;

    void OnAttach(Renderer& renderer, ResourceManager& resourceManager, Scene& scene) override;
    void OnUpdate(float deltaTime) override;
    void OnRender(Renderer& renderer) override;
    void OnImGuiRender(Renderer& renderer) override;
    void OnDetach(Renderer& renderer) override;

    };
}
