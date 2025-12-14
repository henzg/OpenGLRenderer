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
    class TestSquare : public Test
    {
    private:
        ResourceManager* m_ResourceManager = nullptr;
        VertexArray* m_VAO = nullptr;
        VertexBuffer* m_VBO = nullptr;
        IndexBuffer* m_IndexBuffer = nullptr;
        Shader* m_Shader = nullptr;
        Texture* m_Texture1 = nullptr;
        Texture* m_Texture2 = nullptr;

        float m_SquareVerticies[5*4] = 
        {
            .5f,   .5f, 0.f, 1.f, 1.f, // 0 3fpos, 2ftex
            .5f,  -.5f, 0.f, 1.f, 0.f, // 1
            -.5f, -.5f, 0.f, 0.f, 0.f, // 2
            -.5f,  .5f, 0.f, 0.f, 1.f  // 3
        };
        const unsigned int m_SquareIndicies[3*2] =
        {
            0,1,2,
            2,3,0
        };

        std::string m_SquareVertexShader = "../shaders/Square.vs";
        std::string m_SquareFragmentShader = "../shaders/Square.fs";
        glm::vec4 m_SquareColor;
        bool m_SquareWireFrame = false;
        bool m_ShowWireFrame = false;
        float m_TextureMix = 0.f;
    public:
        TestSquare(const std::string& name, ResourceManager& resourceManager, Scene& scene);
        ~TestSquare();

        void OnAttach(Renderer& renderer, ResourceManager& resourceManager, Scene& scene) override;
        void OnUpdate(float deltaTime) override;
        void OnRender(Renderer& render) override;
        void OnImGuiRender(Renderer& renderer) override;
        void OnDetach(Renderer& renderer) override;
    };
}
