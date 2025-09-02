#include "tests/Test3DBasics.h"
#include "Shader.h"
#include "Data.h"

#include "ImguiWidget.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "glm/ext/matrix_transform.hpp"

namespace test {
    Test3DBasics::Test3DBasics(const std::string& name)
        : Test(name)
    {}
    Test3DBasics::~Test3DBasics(){}
    
    void Test3DBasics::OnAttach(Renderer& renderer)
    {
        /*--- OGL Init settings ----------------------------------------------------------------*/
        glEnable(GL_DEPTH_TEST);        
        /*--- Add imgui widgets for this test -------------------------------------------------*/
        renderer.AddDevWindowWidget<ImguiSliderFloat>("Mix Value", &m_TextureMix, 0.0f, 1.0f);
        renderer.AddDevWindowWidget<ImguiSliderFloat>("FOV", &m_Fov, 25.0f, 175.0f);
        renderer.AddDevWindowWidget<ImguiColorEdit4>("Clear Color", &m_WinColor);
        /*--- Add Shaders -------------------------------------------------------------------*/
        m_Shader = std::make_unique<Shader>(m_CubeVertexShader.c_str(), m_CubeFragmentShader.c_str());
        /*--- Add Textures ----------------------------------------------------------------*/ 
        renderer.AddTexture("woodTex", "../res/wood.png", false, false);
        renderer.AddTexture("awesomeFace", "../res/awesomeface.png", true, true);
        if(m_Shader)
        {
            m_Shader->Bind();
            m_Shader->setInt("texture1", 0);
            m_Shader->setInt("texture2", 1);
        }
        /*--- AddLayout --------------------------------------------------------------------*/
        VertexBufferLayout cubeLayout = {
            {ShaderDataType::Float3, "aPos"},
            {ShaderDataType::Float2, "aTexture"}
        };
        /*--- Add Meshes ------------------------------------------------------------------*/    

        renderer.AddMesh("mainCube", m_CubeVerticies, sizeof(m_CubeVerticies) / (5 * sizeof(float)), 
                m_CubeIndicies, sizeof(m_CubeIndicies) / sizeof(unsigned int),
                cubeLayout, "cubeShader", {"woodTex", "awesomeFace"});
    }   

    void Test3DBasics::OnUpdate(float deltaTime) {}
    void Test3DBasics::OnRender(Renderer& renderer) 
    {
        glClearColor(m_WinColor.x, m_WinColor.y, m_WinColor.z, m_WinColor.w);
        glClear(GL_COLOR_BUFFER_BIT);
        /*--- Bind Textures ----------------------------------------------------------------*/
        Texture* tex1 = renderer.GetTexture("woodTex");
        Texture* tex2 = renderer.GetTexture("awesomeFace");
        if (tex1) tex1->BindandActivate(GL_TEXTURE0);
        if (tex2) tex2->BindandActivate(GL_TEXTURE1);        
        /*--- Activate Shaders and Matrixes-------------------------------------------------*/
        m_Shader->Bind();
        m_Shader->setFloat("TextureMix", m_TextureMix);

        // projection matrix
        glm::mat4 projection = glm::perspective(glm::radians(m_Fov),
                                                static_cast<float>(renderer.GetWindowWidth()) / renderer.GetWindowHeight(),
                                                    0.1f, 100.0f);
        m_Shader->setMat4("projection", projection);
        // view matrix
        m_Shader->setMat4("view", renderer.GetCameraViewMatrix());
        const auto& meshes = renderer.GetMeshes();
        for (size_t i = 0; i < meshes.size(); ++i)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 25.0f * (float)glfwGetTime();
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            m_Shader->setMat4("model", model);
            meshes[i]->Draw();
        }

    }
    void Test3DBasics::OnImGuiRender(Renderer& renderer) {}
    void Test3DBasics::OnDetach(Renderer& renderer) {
        glDisable(GL_DEPTH_TEST);
    }
}
