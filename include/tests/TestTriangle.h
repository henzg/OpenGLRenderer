#pragma once

#include "tests/Test.h"
#include "Shader.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

#include <memory>

namespace test 
{
    class TestTriangle : public Test
    {
    private:
    std::unique_ptr<VertexArray> m_VAO;
    std::unique_ptr<IndexBuffer> m_IndexBuffer;
    std::unique_ptr<Shader> m_Shader;

    const char* m_VertexShaderPath = "../shaders/Basic.vs";
    const char* m_FragmentShaderPath = "../shaders/Basic.fs";

    float m_Verticies[3*3] = {
        -.5f, -.5f, .0f,
         .5f, -.5f, .0f,
         .0f,  .5f, .0f
    };

    public:
        TestTriangle(const std::string& name);
        ~TestTriangle();

        void OnAttach(Renderer& renderer) override; // inits buffers and shaders and such
        void OnUpdate(float deltaTime) override;
        void OnRender(Renderer& render) override;
        void OnImGuiRender(Renderer& renderer) override;
        void OnDetach(Renderer& renderer) override;
    
    };

/*--- End of Namespace----------------------------------------------------------------------*/
}

