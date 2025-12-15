#pragma once

#include "Test.h"
#include "Shader.h"
#include "Mesh.h"

#include <memory>
#include "glm/glm.hpp"


namespace test {

    class Test3DBasics : public Test 
    {
    private:
        Shader* m_Shader = nullptr;
        const Mesh* m_Mesh = nullptr;

        std::string m_CubeVertexShader = "../shaders/Cube.vs";
        std::string m_CubeFragmentShader = "../shaders/Cube.fs";

        float m_TextureMix = 0.0f;
        float m_Fov = 90.0f;
        glm::vec3 m_WinColor = {.2f, 0.3f, .3f};

    public:
        Test3DBasics(const std::string& name, ResourceManager& resourceManager, Scene& scene);
        ~Test3DBasics();
        
        void OnAttach(Renderer& renderer, ResourceManager& resourceManager, Scene& scene) override;
        void OnUpdate(float deltaTime) override;
        void OnRender(Renderer& renderer) override;
        void OnImGuiRender(Renderer& renderer) override;
        void OnDetach(Renderer& renderer) override;

    };
}
