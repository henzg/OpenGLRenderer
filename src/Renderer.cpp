#include "Renderer.h"

#include "Core.h"
#include "tests/TestCore.h"
#include "tests/TestLightingMaps.h"
#include <GLFW/glfw3.h>

Renderer::Renderer(const std::string& title, int width, int height)
    : m_Window(title, width, height), 
      m_ImGuiSystem(m_Window.getNativeHandler()),
      m_DevWindow(title, ImVec2(800,800), ImVec2(700,800)),
      m_Camera(),
      m_CurrentWinColor(m_DefaultWinColor)
{}

Renderer::~Renderer() {}

void Renderer::OnInit() 
{
    /*--- OGL init settings ----------------------------------------------------------------*/
    GLClearError();
    GLCall(glClearColor(m_CurrentWinColor[0], m_CurrentWinColor[1], m_CurrentWinColor[2], 1.0f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    /*--- Register Tests--------------------------------------------------------------------*/
     
    m_DevWindow.RegisterTest<test::TestClearColor>("Clear Color Test");
    m_DevWindow.RegisterTest<test::TestTriangle>("Triangle Test");
    m_DevWindow.RegisterTest<test::TestSquare>("Test Square");
    m_DevWindow.RegisterTest<test::Test3DBasics>("A Cube");
    m_DevWindow.RegisterTest<test::TestLighting>("Lighting");
    m_DevWindow.RegisterTest<test::TestMaterials>("Materials");
    m_DevWindow.RegisterTest<test::TestLightingMaps>("Lighting Maps");
}

void Renderer::OnRun() {
    while (!ShouldClose())
    {
        
        /*--- per-frame logic --------------------------------------------------------------*/
        GLClearError();
        
        GLCall(glClearColor(m_CurrentWinColor[0], m_CurrentWinColor[1], m_CurrentWinColor[2], 1.0));
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        float currentFrame = static_cast<float>(glfwGetTime());
        m_DeltaTime = currentFrame - m_LastFrame;
        m_LastFrame = currentFrame;
        ProcessInput();
        /*----------------------------------------------------------------------------------*/
        // imgui
        m_ImGuiSystem.begin_frame();
        m_DevWindow.Draw(m_Window.getWidth(), m_Window.getHeight(), *this, m_DeltaTime);
        m_ImGuiSystem.end_frame();

        // swap buffers and pollevents
        m_Window.swapBuffers();
        m_Window.pollEvents();
    }
}

/* Wrapper function for glfwwindow.shouldClose(); */
bool Renderer::ShouldClose() const 
{
    return m_Window.shouldClose();
}

void Renderer::SetClearColor(float r, float g, float b)
{
    m_CurrentWinColor[0] = r;
    m_CurrentWinColor[1] = g;
    m_CurrentWinColor[2] = b;
}

void Renderer::SetClearColor(glm::vec3 color)
{
    m_CurrentWinColor[0] = color[0];
    m_CurrentWinColor[1] = color[1];
    m_CurrentWinColor[2] = color[2];
}

void Renderer::SetClearColor(ImVec4 color)
{
    m_CurrentWinColor[0] = color.x;
    m_CurrentWinColor[1] = color.y;
    m_CurrentWinColor[2] = color.z;
}

/* Add a mesh to the mesh vector for rendering */
void Renderer::AddMesh(const std::string& name, const float* verticies, unsigned int numVerticies, 
                       const unsigned int* indicies, unsigned int numIndicies, const VertexBufferLayout& layout,
                       const std::string& shaderName, const std::vector<std::string>& textureNames)
{
    m_Meshes.push_back(std::make_unique<Mesh>(verticies, numVerticies, indicies, numIndicies, layout));
}

void Renderer::ClearMeshes()
{
    m_Meshes.clear();
}


/* Add a shader to the Shader map to use for rendering. Has a unique name, and shader object */
void Renderer::AddShader(const std::string& name, const std::string& vsPath, const std::string& fsPath)
{
    m_Shaders.emplace(name, std::make_unique<Shader>(vsPath.c_str(), fsPath.c_str()));
}

Shader* Renderer::GetShader(const std::string& name)
{
    auto it = m_Shaders.find(name);
    if (it != m_Shaders.end())
        if (it->second->IsValid())
            return it->second.get();
    std::cout << "ERROR||FIND||SHADER||" << name << "||NOT FOUND||\n";
    return nullptr;
}

void Renderer::AddTexture(const std::string& name, const std::string& filePath, bool flip_on_load, bool hasAlpha)
{
    std::unique_ptr<Texture> newTexture = std::make_unique<Texture>();
    newTexture->LoadFromFile(filePath, flip_on_load, hasAlpha);
    m_Textures.emplace(name, std::move(newTexture));
}

Texture* Renderer::GetTexture(const std::string& name)
{
    auto it = m_Textures.find(name);
    if (it != m_Textures.end())
        return it->second.get();
    std::cout << "ERROR||FIND||TEXTURE||" << name << "||NOT FOUND||\n";
    return nullptr;
}

void Renderer::ProcessInput()
{
    if(glfwGetKey(m_Window.getNativeHandler(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_Window.getNativeHandler(), true);
    if(glfwGetKey(m_Window.getNativeHandler(), GLFW_KEY_A) == GLFW_PRESS)
        m_Camera.ProcessKeyboardActions(Camera::CameraMovement::LEFT, m_DeltaTime);
    if(glfwGetKey(m_Window.getNativeHandler(), GLFW_KEY_E) == GLFW_PRESS)
        m_Camera.ProcessKeyboardActions(Camera::CameraMovement::BACKWARD, m_DeltaTime);
    if(glfwGetKey(m_Window.getNativeHandler(), GLFW_KEY_D) == GLFW_PRESS)
        m_Camera.ProcessKeyboardActions(Camera::CameraMovement::RIGHT, m_DeltaTime);
    if(glfwGetKey(m_Window.getNativeHandler(), GLFW_KEY_Q) == GLFW_PRESS)
        m_Camera.ProcessKeyboardActions(Camera::CameraMovement::FORWARD, m_DeltaTime);
    if(glfwGetKey(m_Window.getNativeHandler(), GLFW_KEY_W) == GLFW_PRESS)
       m_Camera.ProcessKeyboardActions(Camera::CameraMovement::UP, m_DeltaTime);
    if(glfwGetKey(m_Window.getNativeHandler(), GLFW_KEY_S) == GLFW_PRESS)
        m_Camera.ProcessKeyboardActions(Camera::CameraMovement::DOWN, m_DeltaTime);
}

void Renderer::OnCleanup() {
    glfwTerminate();
}
