#include "tests/Test3DBasics.h"
#include "Shader.h"
#include "Data.h"

#include "ImguiWidget.h"
#include "Renderer.h"
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
        /*--------------------------------------------------------------------------------------*/
        /*--- Add imgui widgets for this test -------------------------------------------------*/
        renderer.AddDevWindowWidget<ImguiSliderFloat>("Mix Value", &m_TextureMix, 0.0f, 1.0f);
        renderer.AddDevWindowWidget<ImguiSliderFloat>("FOV", &m_Fov, 25.0f, 175.0f);
        renderer.AddDevWindowWidget<ImguiColorPicker4>("Clear Color", &m_WinColor, true);
        /*------------------------------------------------------------------------------------*/
        /*--- Add Shaders -------------------------------------------------------------------*/
        renderer.AddShader("texShader", "../shaders/texshader.vs", "../shaders/texshader.fs");
        Shader* texShader = renderer.GetShader("texShader");
        if (texShader)
        {
            texShader->use();
            texShader->setInt("texture1", 0);
            texShader->setInt("texture2", 1);
        }
        /*----------------------------------------------------------------------------------*/
        /*--- Add Textures ----------------------------------------------------------------*/
        renderer.AddTexture("woodTex", "../res/wood.png", false, false);
        renderer.AddTexture("awesomeFace", "../res/awesomeface.png", true, true);
        /*----------------------------------------------------------------------------------*/
        /*--- Add Meshes ------------------------------------------------------------------*/    
        VertexBufferLayout cubeLayout = {
            {ShaderDataType::Float3, "a_Position"},
            {ShaderDataType::Float2, "textCords"}
        };

        renderer.AddMesh("mainCube", cubeverticies, sizeof(cubeverticies) / (5 * sizeof(float)), 
                cubeIndicies, sizeof(cubeIndicies) / sizeof(unsigned int),
                cubeLayout, "texShader", {"woodTex", "awesomeFace"});
        /*----------------------------------------------------------------------------------*/
    }   

    void Test3DBasics::OnUpdate(float deltaTime) {}
    void Test3DBasics::OnRender(Renderer& renderer) 
    {
        /*--- Bind Textures ----------------------------------------------------------------*/
        Texture* tex1 = renderer.GetTexture("woodTex");
        Texture* tex2 = renderer.GetTexture("awesomeFace");
        if (tex1) tex1->BindandActivate(GL_TEXTURE0);
        if (tex2) tex2->BindandActivate(GL_TEXTURE1);        
        /*----------------------------------------------------------------------------------*/
        /*--- Activate Shaders and Matrixes-------------------------------------------------*/
        Shader* currentShader = renderer.GetShader("texShader");
        if (currentShader)
        {
            currentShader->use();
            currentShader->setFloat("texvis", m_TextureMix);

            // projection matrix
            glm::mat4 projection = glm::perspective(glm::radians(m_Fov), 
                                                    static_cast<float>(renderer.GetWindowWidth()) / renderer.GetWindowHeight(),
                                                    0.1f, 100.0f);
            currentShader->setMat4("projection", projection);
            // view matrix
            currentShader->setMat4("view", renderer.GetCameraViewMatrix());
            const auto& meshes = renderer.GetMeshes();
            for (size_t i = 0; i < meshes.size(); ++i)
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, cubePositions[i]);
                float angle = 25.0f * (float)glfwGetTime();
                model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
                currentShader->setMat4("model", model);

                meshes[i]->Draw();
            }

        } else {
            std::cerr << "ERROR||SHADER||INITIALIZATION\n";
        }
    }
    void Test3DBasics::OnImGuiRender(Renderer& renderer) {}
    void Test3DBasics::OnDetach(Renderer& renderer) {}
}
