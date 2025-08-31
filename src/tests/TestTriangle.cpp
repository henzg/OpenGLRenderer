#include "tests/TestTriangle.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"


namespace test
{
    TestTriangle::TestTriangle(const std::string& name)
        : Test(name)
    {}

    void TestTriangle::OnAttach(Renderer& renderer)
    {
        m_VAO = std::make_unique<VertexArray>();
        VertexBuffer vbo(m_Verticies, 3*3 * sizeof(float));
        m_Shader = std::make_unique<Shader>(m_VertexShaderPath, m_FragmentShaderPath);
        VertexBufferLayout layout = 
        {
            {ShaderDataType::Float3, "aPos"},
        };

        m_VAO->AddBuffer(vbo, layout);
        
    }

    void OnUpdate(float deltaTime) {}
    void OnRender(Renderer& renderer) 
    {}
    void OnImGuiRender(Renderer& renderer) {}
    void OnDetach(Renderer& renderer) {}


/*--- End of test namespace-----------------------------------------------------------------*/
}
