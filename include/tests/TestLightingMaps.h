#pragma once
#include "tests/Test.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include "Texture.h"

#include <memory>


namespace test {
    class TestLightingMaps : public Test {
private:
    std::unique_ptr<VertexArray> m_ObjVAO;
    std::unique_ptr<VertexArray> m_LightVAO;
    std::unique_ptr<VertexBuffer> m_VBO;
    std::unique_ptr<Shader> m_LightingShader;
    std::unique_ptr<Shader> m_LightCubeShader;
    std::unique_ptr<Texture> m_Texture;
    
    std::string m_LightingMapVS;
    std::string m_LightingMapFS;
    std::string m_LightCubeVS;
    std::string m_LightCubeFS;
    
    glm::vec3 m_LightAmbient = glm::vec3(1.f);
    glm::vec3 m_LightDiffuse = glm::vec3(1.f);
    glm::vec3 m_LightSpecular = glm::vec3(1.f);
    glm::vec3 m_LightPosition = {1.2f, 1.f, 2.f};

    float m_Verticies[8*36] = 
    {
        // pos[0:2] normal[3:5] tex[6:7]
        -0.5f, -0.5f, -0.5f, 0.f, 0.f, -1.f, 0.f, 0.f,  
         0.5f, -0.5f, -0.5f, 0.f, 0.f, -1.f, 1.f, 0.f, 
         0.5f,  0.5f, -0.5f, 0.f, 0.f, -1.f, 1.f, 1.f,
         0.5f,  0.5f, -0.5f, 0.f, 0.f, -1.f, 1.f, 1.f,
        -0.5f,  0.5f, -0.5f, 0.f, 0.f, -1.f, 0.f, 1.f,
        -0.5f, -0.5f, -0.5f, 0.f, 0.f, -1.f, 0.f, 0.f,

        -0.5f, -0.5f,  0.5f,  0.f, 0.f, 1.f, 0.f, 0.f,
         0.5f, -0.5f,  0.5f,  0.f, 0.f, 1.f, 1.f, 0.f,
         0.5f,  0.5f,  0.5f,  0.f, 0.f, 1.f, 1.f, 1.f,
         0.5f,  0.5f,  0.5f,  0.f, 0.f, 1.f, 1.f, 1.f,
        -0.5f,  0.5f,  0.5f,  0.f, 0.f, 1.f, 0.f, 1.f,
        -0.5f, -0.5f,  0.5f,  0.f, 0.f, 1.f, 0.f, 0.f,

        -0.5f,  0.5f,  0.5f, -1.f, 0.f, 0.f, 0.f, 1.f,
        -0.5f,  0.5f, -0.5f, -1.f, 0.f, 0.f, 0.f, 1.f,
        -0.5f, -0.5f, -0.5f, -1.f, 0.f, 0.f, 0.f, 0.f,
        -0.5f, -0.5f, -0.5f, -1.f, 0.f, 0.f, 0.f, 0.f,
        -0.5f, -0.5f,  0.5f, -1.f, 0.f, 0.f, 0.f, 0.f,
        -0.5f,  0.5f,  0.5f, -1.f, 0.f, 0.f, 0.f, 1.f,

         0.5f,  0.5f,  0.5f,  1.f, 0.f, 0.f, 1.f, 1.f,  
         0.5f,  0.5f, -0.5f,  1.f, 0.f, 0.f, 1.f, 1.f,
         0.5f, -0.5f, -0.5f,  1.f, 0.f, 0.f, 1.f, 0.f,
         0.5f, -0.5f, -0.5f,  1.f, 0.f, 0.f, 1.f, 0.f,
         0.5f, -0.5f,  0.5f,  1.f, 0.f, 0.f, 1.f, 0.f,
         0.5f,  0.5f,  0.5f,  1.f, 0.f, 0.f, 1.f, 1.f,

        -0.5f, -0.5f, -0.5f,  0.f,-1.f, 0.f, 0.f, 0.f,
         0.5f, -0.5f, -0.5f,  0.f,-1.f, 0.f, 1.f, 0.f,
         0.5f, -0.5f,  0.5f,  0.f,-1.f, 0.f, 1.f, 0.f,
         0.5f, -0.5f,  0.5f,  0.f,-1.f, 0.f, 1.f, 0.f,
        -0.5f, -0.5f,  0.5f,  0.f,-1.f, 0.f, 0.f, 0.f,
        -0.5f, -0.5f, -0.5f,  0.f,-1.f, 0.f, 0.f, 0.f,

        -0.5f,  0.5f, -0.5f,  0.f, 1.f, 0.f, 0.f, 1.f,
         0.5f,  0.5f, -0.5f,  0.f, 1.f, 0.f, 1.f, 1.f,
         0.5f,  0.5f,  0.5f,  0.f, 1.f, 0.f, 1.f, 1.f,
         0.5f,  0.5f,  0.5f,  0.f, 1.f, 0.f, 1.f, 1.f,
        -0.5f,  0.5f,  0.5f,  0.f, 1.f, 0.f, 0.f, 1.f,
        -0.5f,  0.5f, -0.5f,  0.f, 1.f, 0.f, 0.f, 1.f
    };

public:
    TestLightingMaps(const std::string& name);
    ~TestLightingMaps() = default;


    void OnAttach(Renderer& renderer) override;
    void OnUpdate(float deltaTime) override;
    void OnRender(Renderer& renderer) override;
    void OnImGuiRender(Renderer& renderer) override;
    void OnDetach(Renderer& renderer) override;

    };
}
