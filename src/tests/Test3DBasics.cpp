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
        renderer.EnableDepthTest(true);
        /*--- Add imgui widgets for this test -------------------------------------------------*/
        renderer.AddDevWindowWidget<ImguiSliderFloat>("Mix Value", &m_TextureMix, 0.0f, 1.0f);
        renderer.AddDevWindowWidget<ImguiSliderFloat>("FOV", &m_Fov, 25.0f, 175.0f);
        renderer.AddDevWindowWidget<ImguiColorEdit3>("Clear Color", &m_WinColor);
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
        /*--- Add Mesh --------------------------------------------------------------------*/
        renderer.AddMesh("mainCube", std::move(m_Mesh));
    }   

    void Test3DBasics::OnUpdate(float deltaTime) {}
    void Test3DBasics::OnRender(Renderer& renderer) 
    {
        renderer.SetClearColor(m_WinColor);
        
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
        const auto& mesh = renderer.GetMesh("mainCube");
        if(mesh)
        {
        for (size_t i = 0; i < 1; ++i)
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, cubePositions[i]);
                float angle = 25.0f * (float)glfwGetTime();
                model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
                m_Shader->setMat4("model", model);
                mesh->Draw();
            }
        } else {
            std::cerr << "||ERROR||COULD NOT FIND MESH||\n";
        }

    }
    void Test3DBasics::OnImGuiRender(Renderer& renderer) {}
    void Test3DBasics::OnDetach(Renderer& renderer) {
        renderer.ClearMeshes();
        renderer.ClearDevWindowWidgets();
        renderer.EnableDepthTest(false);
    
    }
}
