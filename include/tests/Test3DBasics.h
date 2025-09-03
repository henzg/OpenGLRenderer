#pragma once

#include "Test.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "imgui/imgui.h"

#include <memory>


namespace test {

    class Test3DBasics : public Test 
    {
    private:
        std::unique_ptr<VertexBuffer> m_VBO;
        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<IndexBuffer> m_IndexBuffer;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<Texture> m_Texture;
        std::unique_ptr<Mesh> m_Mesh;

        std::string m_CubeVertexShader = "../shaders/Cube.vs";
        std::string m_CubeFragmentShader = "../shaders/Cube.fs";
        
        float m_CubeVerticies[5*24] =
        {
            // Positions            // Texture Coords

            // Front face
            -0.5f, -0.5f,  0.5f,   0.0f, 0.0f, // 0 - Bottom-left
            0.5f, -0.5f,  0.5f,   1.0f, 0.0f, // 1 - Bottom-right
            0.5f,  0.5f,  0.5f,   1.0f, 1.0f, // 2 - Top-right
            -0.5f,  0.5f,  0.5f,   0.0f, 1.0f, // 3 - Top-left

            // Back face
            -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, // 4 - Bottom-left
            0.5f, -0.5f, -0.5f,   1.0f, 0.0f, // 5 - Bottom-right
            0.5f,  0.5f, -0.5f,   1.0f, 1.0f, // 6 - Top-right
            -0.5f,  0.5f, -0.5f,   0.0f, 1.0f, // 7 - Top-left

            // Left face
            -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, // 8 - Bottom-left (relative to this face)
            -0.5f, -0.5f,  0.5f,   1.0f, 0.0f, // 9 - Bottom-right
            -0.5f,  0.5f,  0.5f,   1.0f, 1.0f, // 10 - Top-right
            -0.5f,  0.5f, -0.5f,   0.0f, 1.0f, // 11 - Top-left

            // Right face
            0.5f, -0.5f,  0.5f,   0.0f, 0.0f, // 12 - Bottom-left
            0.5f, -0.5f, -0.5f,   1.0f, 0.0f, // 13 - Bottom-right
            0.5f,  0.5f, -0.5f,   1.0f, 1.0f, // 14 - Top-right
            0.5f,  0.5f,  0.5f,   0.0f, 1.0f, // 15 - Top-left

            // Top face
            -0.5f,  0.5f,  0.5f,   0.0f, 0.0f, // 16 - Bottom-left
            0.5f,  0.5f,  0.5f,   1.0f, 0.0f, // 17 - Bottom-right
            0.5f,  0.5f, -0.5f,   1.0f, 1.0f, // 18 - Top-right
            -0.5f,  0.5f, -0.5f,   0.0f, 1.0f, // 19 - Top-left

            // Bottom face
            -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, // 20 - Bottom-left
            0.5f, -0.5f, -0.5f,   1.0f, 0.0f, // 21 - Bottom-right
            0.5f, -0.5f,  0.5f,   1.0f, 1.0f, // 22 - Top-right
            -0.5f, -0.5f,  0.5f,   0.0f, 1.0f  // 23 - Top-left
    
        };

        unsigned int m_CubeIndicies[3*12] =
        {
        0,1,2, // bl, br, tr
        2,3,0, // tr, tl, bl
        // back face
        4,5,6,
        6,7,4,
        // left face
        8,9,10,
        10,11,8,
        // right face
        12,13,14,
        14,15,12,
        // top face
        16,17,18,
        18,19,16,
        // bottom face
        20,21,22,
        22,23,20
        };

        float m_TextureMix = 0.0f;
        float m_Fov = 90.0f;
        ImVec4 m_WinColor = {.2f, 0.3f, .3f, 1.f};

    public:
        Test3DBasics(const std::string& name);
        ~Test3DBasics();
        
        void OnAttach(Renderer& renderer) override;
        void OnUpdate(float deltaTime) override;
        void OnRender(Renderer& renderer) override;
        void OnImGuiRender(Renderer& renderer) override;
        void OnDetach(Renderer& renderer) override;

    };
}
