#pragma once

#include "glm/fwd.hpp"
#include "tests/Test.h"
#include "glm/glm.hpp"
#include <memory>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Shader.h"

namespace test
{
    class TestLighting : public Test
    {
    private:
        std::unique_ptr<VertexArray> m_ObjVAO;
        std::unique_ptr<VertexArray> m_LightVAO;
        std::unique_ptr<VertexBuffer> m_VBO;
        std::unique_ptr<Shader> m_LightingShader;
        std::unique_ptr<Shader> m_LightCubeShader;

        std::string m_LightingColorVS = "../shaders/Lighting.vs";
        std::string m_LightingColorFS = "../shaders/Lighting.fs";
        std::string m_LightCubeVS = "../shaders/CoreLight.vs";
        std::string m_LightCubeFS = "../shaders/CoreLight.fs";

        glm::vec3 m_ObjectColor = {1.f, .5f, .31f};
        glm::vec3 m_LightColor = {1.f, 1.f, 1.f};

        glm::vec3 m_LightPosition = {1.2f, 1.0f, 2.0f};
        float m_Verticies[3*36] = 
        {
                -0.5f, -0.5f, -0.5f, 
                0.5f, -0.5f, -0.5f,  
                0.5f,  0.5f, -0.5f,  
                0.5f,  0.5f, -0.5f,  
               -0.5f,  0.5f, -0.5f, 
                -0.5f, -0.5f, -0.5f, 

                -0.5f, -0.5f,  0.5f, 
                 0.5f, -0.5f,  0.5f,  
                 0.5f,  0.5f,  0.5f,  
                0.5f,  0.5f,  0.5f,  
                -0.5f,  0.5f,  0.5f, 
                -0.5f, -0.5f,  0.5f, 

                -0.5f,  0.5f,  0.5f, 
                -0.5f,  0.5f, -0.5f, 
                -0.5f, -0.5f, -0.5f, 
                -0.5f, -0.5f, -0.5f, 
                -0.5f, -0.5f,  0.5f, 
                -0.5f,  0.5f,  0.5f, 

                 0.5f,  0.5f,  0.5f,  
                0.5f,  0.5f, -0.5f,  
                 0.5f, -0.5f, -0.5f,  
                0.5f, -0.5f, -0.5f,  
                0.5f, -0.5f,  0.5f,  
                0.5f,  0.5f,  0.5f,  

                -0.5f, -0.5f, -0.5f, 
                0.5f, -0.5f, -0.5f,  
                0.5f, -0.5f,  0.5f,  
                0.5f, -0.5f,  0.5f,  
                -0.5f, -0.5f,  0.5f, 
                -0.5f, -0.5f, -0.5f, 

                -0.5f,  0.5f, -0.5f, 
                0.5f,  0.5f, -0.5f,  
                0.5f,  0.5f,  0.5f,  
                0.5f,  0.5f,  0.5f,  
                -0.5f,  0.5f,  0.5f, 
                -0.5f,  0.5f, -0.5f, 
        };
    public:
        TestLighting(const std::string& name);
        ~TestLighting();
        
        void OnAttach(Renderer& renderer) override;
        void OnUpdate(float deltaTime) override;
        void OnRender(Renderer& renderer) override;
        void OnImGuiRender(Renderer& renderer) override;
        void OnDetach(Renderer& renderer) override;
        
    };
}
