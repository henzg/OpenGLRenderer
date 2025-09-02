#pragma once

#include "tests/Test.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "glm/glm.hpp"

#include <memory>

namespace test 
{
    class TestTriangle : public Test
    {
    private:
    std::unique_ptr<VertexArray> m_VAO;
    std::unique_ptr<VertexBuffer> m_VBO;
    std::unique_ptr<Shader> m_Shader = nullptr;
    const char* m_VertexShaderPath = "../shaders/Basic.vs";
    const char* m_FragmentShaderPath = "../shaders/Basic.fs";

    glm::vec4 m_TriangleColor;
    glm::vec2 m_TriCoords = {.0f, .0f};
    float m_Verticies[3*3] = {
            -.5f, -.5f, 1.0f,
            .5f,  -.5f, 1.0f,
            .0f,   .5f, 1.0f
    };

    float m_Time = 0.0f, m_Speed = 3.f;
    bool m_PartyTime = false;
    bool m_TriCheckboxState = false;
    bool m_TriWireFrameState = false;
    bool m_ShowTriWireFrame = false;

    
    public:
        TestTriangle(const std::string& name);
        ~TestTriangle();

        void OnAttach(Renderer& renderer) override;
        void OnUpdate(float deltaTime) override;
        void OnRender(Renderer& render) override;
        void OnImGuiRender(Renderer& renderer) override;
        void OnDetach(Renderer& renderer) override;
    
    };

/*--- End of Namespace----------------------------------------------------------------------*/
}

