#include "tests/Test3DBasics.h"
#include "Shader.h"
#include "Data.h"

#include "ImguiWidget.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "glm/ext/matrix_transform.hpp"
#include <GLFW/glfw3.h>

namespace test {
    Test3DBasics::Test3DBasics(const std::string& name, ResourceManager& resourceManager, Scene& scene)
        : Test(name, resourceManager, scene)
    {}
    Test3DBasics::~Test3DBasics(){}
    
    void Test3DBasics::OnAttach(Renderer& renderer, ResourceManager& resourceManager, Scene& scene)
    {
        /*--- OGL Init settings ----------------------------------------------------------------*/
        renderer.EnableDepthTest(true);
        /*--- Add imgui widgets for this test -------------------------------------------------*/
        renderer.AddDevWindowWidget<ImguiSliderFloat>("Mix Value", &m_TextureMix, 0.0f, 1.0f);
        renderer.AddDevWindowWidget<ImguiSliderFloat>("FOV", &m_Fov, 25.0f, 175.0f);
        renderer.AddDevWindowWidget<ImguiColorEdit3>("Clear Color", &m_WinColor);
        /*--- Add Shaders -------------------------------------------------------------------*/
        resourceManager.AddShader("CubeShader", m_CubeVertexShader, m_CubeFragmentShader);
        m_Shader = resourceManager.GetShader("CubeShader");
        /*--- Add Textures ----------------------------------------------------------------*/ 
        resourceManager.AddTexture("woodTex", "../res/wood.png", false, false);
        resourceManager.AddTexture("awesomeFace", "../res/awesomeface.png", true, true);
        if(m_Shader)
        {
            m_Shader->Bind();
            m_Shader->setInt("texture1", 0);
            m_Shader->setInt("texture2", 1);
        }
        /*--- Create mesh managed by ResourceManager ----------------------------------------------*/
        resourceManager.AddMesh("BasicsCube", Mesh::CreateCube(CubeFeature::Position | CubeFeature::TexCoord));
        m_Mesh = resourceManager.GetMesh("BasicsCube");

        // Option B: Scene entity (projection/view/model handled by renderer)
        Scene::Entity e{};
        e.mesh = m_Mesh;
        e.shader = m_Shader;
        e.update = [](Scene::Transform& t, const Renderer&) {
            float angle = 25.0f * (float)glfwGetTime();
            t.rotationDeg = glm::vec3(angle, angle * 0.3f, angle * 0.5f);
        };
        e.bind = [this](Shader& shader, const Renderer& r) {
            Texture* tex1 = r.GetResourceManager().GetTexture("woodTex");
            Texture* tex2 = r.GetResourceManager().GetTexture("awesomeFace");
            if (tex1) tex1->BindandActivate(GL_TEXTURE0);
            if (tex2) tex2->BindandActivate(GL_TEXTURE1);
            shader.setFloat("TextureMix", m_TextureMix);
        };
        // Keep the old animated rotation behavior:
        e.transform.position = s_CubePositions[0];
        scene.AddEntity(e);
    }   

    void Test3DBasics::OnUpdate(float deltaTime) {}
    void Test3DBasics::OnRender(Renderer& renderer) 
    {
        renderer.SetClearColor(m_WinColor);
        // Draw is handled by Scene::Entity in Renderer::OnRender(scene)
    }
    void Test3DBasics::OnImGuiRender(Renderer& renderer) {}
    void Test3DBasics::OnDetach(Renderer& renderer) {
        m_Mesh = nullptr;
    }
}
