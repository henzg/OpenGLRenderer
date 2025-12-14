#pragma once

#include "tests/Test.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"

#include <memory>

namespace test
{
    class TestShader : public Test
    {
    private:
        ResourceManager* m_ResourceManager = nullptr;
        VertexArray* m_VAO = nullptr;
        VertexBuffer* m_VBO = nullptr;
        IndexBuffer* m_IndexBuffer = nullptr;
        Shader* m_Shader = nullptr;
        Texture* m_Texture = nullptr;
        const Mesh* m_SquareMesh = nullptr;

        glm::vec3 m_DcOffset= glm::vec3(0.6704, 0.871, .189);
        glm::vec3 m_Amp     = glm::vec3(1.163, -0.171, -2.949);
        glm::vec3 m_Freq    = glm::vec3(-.875, 2.033, 1.217);
        glm::vec3 m_Phase   = glm::vec3(-0.347, 1.746, 2.3456);

        float m_SquareVerticies[5*4] = 
        {
             1.f,  1.f, 0.f, 1.f, 1.f,// 0 3fpos
             1.f, -1.f, 0.f, 1.f, 0.f,// 1
            -1.f, -1.f, 0.f, 0.f, 0.f,// 2
            -1.f,  1.f, 0.f, 0.f, 1.f // 3
        };
        const unsigned int m_SquareIndicies[3*2] =
        {
            0,1,2,
            2,3,0
        };

        std::string m_ShaderArtVS = "../shaders/ShaderArt.vs";
        std::string m_ShaderArtFS = "../shaders/ShaderArt.fs";
        glm::vec4 m_SquareColor = {1.0, 1.0, 1.0, 1.0};
        
                
    public:
        TestShader(const std::string& name, ResourceManager& resourceManager, Scene& scene);
        ~TestShader();

        void OnAttach(Renderer& renderer, ResourceManager& resourceManager, Scene& scene) override;
        void OnUpdate(float deltaTime) override;
        void OnRender(Renderer& render) override;
        void OnImGuiRender(Renderer& renderer) override;
        void OnDetach(Renderer& renderer) override;
    };
}
