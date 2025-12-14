#include "Renderer.h"

#include "Core.h"
#include "tests/TestCore.h"
#include "tests/TestLightCaster.h"
#include "tests/TestLightingMaps.h"
#include "tests/TestShaders.h"
#include <GLFW/glfw3.h>

/* Renderer Class */
/* INFO: The main backend to the application. */

/* Renderer constructor - App name, win width, win height
    ImGuiSystem inits
    DevWindow inits
    Camera inits
    Sets default wincolor as current wincolor
*/
Renderer::Renderer(const std::string& title, int width, int height)
    : m_Window(title, width, height), 
      m_ImGuiSystem(m_Window.getNativeHandler()),
      m_DevWindow(title, ImVec2(800,800), ImVec2(700,800)),
      m_Camera(),
      m_ResourceManager(),
      m_Scene(),
      m_InputManager(m_Window.getNativeHandler(), m_Camera),
      m_CurrentWinColor(m_DefaultWinColor)
{}

/* Renderer deconstructor - defaults nothing fancy */
Renderer::~Renderer() {}

/* When the render inits, run the following function
 * Sets glclearcolor, and clears buffer_bit and depth_buffer_bit 
 * Registers all tests that has been loaded */
void Renderer::OnInit() 
{
    /*--- OGL init settings ----------------------------------------------------------------*/
    GLClearError();
    EnableDepthTest(true);
    GLCall(glClearColor(m_CurrentWinColor[0], m_CurrentWinColor[1], m_CurrentWinColor[2], 1.0f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    /*--- Register Tests--------------------------------------------------------------------*/
    TestRegister(); 
}

/* While the renderer is running do this function */
void Renderer::OnRun() {
    while (!ShouldClose())
    {
        /*--- per-frame logic --------------------------------------------------------------*/
        GLClearError();

        float currentFrame = static_cast<float>(glfwGetTime());
        m_DeltaTime = currentFrame - m_LastFrame;
        m_LastFrame = currentFrame;

        if (m_DevWindow.GetCurrentTest()) {
            m_DevWindow.GetCurrentTest()->OnUpdate(m_DeltaTime);
        }

        GLCall(glClearColor(m_CurrentWinColor[0], m_CurrentWinColor[1], m_CurrentWinColor[2], 1.0));
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Allow the active test to draw after clearing.
        if (m_DevWindow.GetCurrentTest()) {
            m_DevWindow.GetCurrentTest()->OnRender(*this);
        }

        OnRender(m_Scene); // Render objects from the scene

        /*----------------------------------------------------------------------------------*/
        // imgui
        m_ImGuiSystem.begin_frame();
        m_DevWindow.Draw(m_Window.getWidth(), m_Window.getHeight(), *this, m_DeltaTime, m_Scene);
        m_ImGuiSystem.end_frame();

        m_InputManager.Update(m_DeltaTime); // Update input after ImGui has processed events

        // swap buffers and pollevents
        m_Window.swapBuffers();
        m_Window.pollEvents();
    }
}

void Renderer::OnRender(Scene& scene)
{
    // Update camera and process input (will be moved to InputManager later)
    // These are now handled by the InputManager

    // Render all renderable objects in the scene
    glm::mat4 view = scene.GetCamera().GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(scene.GetCamera().GetZoom()), 
                                            (float)m_Window.getWidth() / (float)m_Window.getHeight(), 0.1f, 100.f);

    for (const auto& renderable : scene.GetRenderables())
    {
        renderable->Draw(*this, view, projection);
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



















void Renderer::TestRegister() {

    m_DevWindow.RegisterTest<test::TestClearColor>("Clear Color Test", m_ResourceManager, m_Scene);
    m_DevWindow.RegisterTest<test::TestTriangle>("Triangle Test", m_ResourceManager, m_Scene);
    m_DevWindow.RegisterTest<test::TestSquare>("Test Square", m_ResourceManager, m_Scene);
    m_DevWindow.RegisterTest<test::Test3DBasics>("A Cube", m_ResourceManager, m_Scene);
    m_DevWindow.RegisterTest<test::TestLighting>("Lighting", m_ResourceManager, m_Scene);
    m_DevWindow.RegisterTest<test::TestMaterials>("Materials", m_ResourceManager, m_Scene);
    m_DevWindow.RegisterTest<test::TestLightingMaps>("Lighting Maps", m_ResourceManager, m_Scene);
    //m_DevWindow.RegisterTest<test::TestLightCaster>("Light Casters", *this);
    m_DevWindow.RegisterTest<test::TestShader>("Shader Art Bonus", m_ResourceManager, m_Scene);
}


void Renderer::OnCleanup() {
    glfwTerminate();
}

