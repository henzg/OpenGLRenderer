#include "tests/TestLighting.h"

#include "ImguiWidget.h"
#include "VertexBufferLayout.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Renderer.h"


namespace test 
{
    TestLighting::TestLighting(const std::string& name)
        : Test(name) {}

    TestLighting::~TestLighting() {}

    
        void TestLighting::OnAttach(Renderer& renderer) 
        {

            renderer.AddDevWindowWidget<ImguiDragFloat3>("Light Pos", &m_LightPosition, .05);        

            glEnable(GL_DEPTH_TEST);
            m_ObjVAO = std::make_unique<VertexArray>();
            m_VBO = std::make_unique<VertexBuffer>(m_Verticies, sizeof(m_Verticies));
            VertexBufferLayout cubeLayout =
        {
            {ShaderDataType::Float3, "aPos"},
            {ShaderDataType::Float3, "aNormal"},
        };
            m_ObjVAO->AddBuffer(*m_VBO, cubeLayout);
            m_ObjVAO->Unbind();
            
            m_LightVAO = std::make_unique<VertexArray>();
            m_LightVAO->AddBuffer(*m_VBO, cubeLayout);
            m_LightVAO->Unbind();

            m_LightingShader = std::make_unique<Shader>(m_LightingColorVS.c_str(), m_LightingColorFS.c_str());
            m_LightCubeShader = std::make_unique<Shader>(m_LightCubeVS.c_str(), m_LightCubeFS.c_str());
        }

        void TestLighting::OnUpdate(float deltaTime) {}
        void TestLighting::OnRender(Renderer& renderer) 
        {
            m_LightingShader->Bind();
            m_LightingShader->setVec3("objectColor", m_ObjectColor);
            m_LightingShader->setVec3("lightColor", m_LightColor);
            m_LightingShader->setVec3("lightPos", m_LightPosition);
            glm::mat4 projection = glm::perspective(glm::radians(renderer.GetCameraZoom()), (float)renderer.GetWindowWidth() / (float)renderer.GetWindowHeight(), 0.1f, 100.f);
            glm::mat4 view = renderer.GetCameraViewMatrix();
            m_LightingShader->setMat4("projection", projection);
            m_LightingShader->setMat4("view", view);

            glm::mat4 model = glm::mat4(1.f);
            m_LightingShader->setMat4("model", model);

            m_ObjVAO->Bind();
            glDrawArrays(GL_TRIANGLES, 0, 36);
            m_ObjVAO->Unbind();
        
            m_LightCubeShader->Bind();
            m_LightCubeShader->setMat4("projection", projection);
            m_LightCubeShader->setMat4("view", view);
            model = glm::mat4(1.f);
            model = glm::translate(model, m_LightPosition);
            model = glm::scale(model, glm::vec3(0.2f));
            m_LightCubeShader->setMat4("model", model);

            m_LightVAO->Bind();
            glDrawArrays(GL_TRIANGLES, 0, 36);
            
        }
        void TestLighting::OnImGuiRender(Renderer& renderer) {}
        void TestLighting::OnDetach(Renderer& renderer) 
        {
            glDisable(GL_DEPTH_TEST);
        }

}
