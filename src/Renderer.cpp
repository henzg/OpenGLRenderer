#include "Renderer.h"

#include "Core.h"
#include <GLFW/glfw3.h>

#include "tests/TestClearColor.h"
#include "tests/TestTriangle.h"

Renderer::Renderer(const std::string& title, int width, int height)
    : m_Window(title, width, height), 
      m_ImGuiSystem(m_Window.getNativeHandler()),
      m_DevWindow(title, ImVec2(800,800), ImVec2(700,800)),
      m_Camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f))
{}

Renderer::~Renderer() {}

void Renderer::Init() 
{
    /*--- OGL init settings ----------------------------------------------------------------*/
    GLClearError();
    //GLCall(glEnable(GL_DEPTH_TEST));
    GLCall(glClearColor(m_WinColor.x, m_WinColor.y, m_WinColor.z, m_WinColor.w));
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    /*--------------------------------------------------------------------------------------*/
     
    m_DevWindow.RegisterTest<test::TestClearColor>("Clear Color Test");
    m_DevWindow.RegisterTest<test::TestTriangle>("Triangle Test");
    /*Add shaders*/
    /*render
    AddShader("texShader", "../shaders/texshader.vs", "../shaders/texshader.fs");
    Shader* texShader = GetShader("texShader");
    if (texShader)
    {
        texShader->use();
        texShader->setInt("texture1", 0);
        texShader->setInt("texture2", 1);
    }
    */
    /*Add Textures*/
    /*
    AddTexture("woodTex", "../res/wood.png", false, false);
    AddTexture("awesomeFace", "../res/awesomeface.png", true, true);
    */
    /*Add Meshes*/
    /*
    VertexBufferLayout cubeLayout = {
        {ShaderDataType::Float3, "a_Position"},
        {ShaderDataType::Float2, "textCords"}
    };

    AddMesh("mainCube", cubeverticies, sizeof(cubeverticies) / (5 * sizeof(float)), 
            cubeIndicies, sizeof(cubeIndicies) / sizeof(unsigned int),
           cubeLayout, "texShader", {"woodTex", "awesomeFace"});
    */
}

void Renderer::Run() {
    while (!ShouldClose())
    {
        
        /*--- per-frame logic --------------------------------------------------------------*/
        GLClearError();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        float currentFrame = static_cast<float>(glfwGetTime());
        m_DeltaTime = currentFrame - m_LastFrame;
        m_LastFrame = currentFrame;
        ProcessInput();
        /*----------------------------------------------------------------------------------*/

        /*
        // Bind Textures
        Texture* tex1 = GetTexture("woodTex");
        Texture* tex2 = GetTexture("awesomeFace");
        if (tex1) tex1->BindandActivate(GL_TEXTURE0);
        if (tex2) tex2->BindandActivate(GL_TEXTURE1);

        // activate shaders
        Shader* currentShader = GetShader("texShader");
        if (currentShader)
        {
            currentShader->use();
            currentShader->setFloat("texvis", m_TexVis);

            // projection matrix
            glm::mat4 projection = glm::perspective(glm::radians(m_Fov), 
                                                    static_cast<float>(m_Window.getWidth()) / m_Window.getHeight(),
                                                    0.1f, 100.0f);
            currentShader->setMat4("projection", projection);
            // view
            //glm::mat4 view = m_Camera.GetViewMatrix();
            currentShader->setMat4("view", m_Camera.GetViewMatrix());

            for (size_t i = 0; i < m_Meshes.size(); ++i)
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, cubePositions[i]);
                float angle = 25.0f * (float)glfwGetTime();
                model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
                currentShader->setMat4("model", model);

                m_Meshes[i]->Draw();
            }

        } else {std::cerr << "Shader not initilaized\n";}
        */
        //*--- Rendering--------------------------------------------------------------------*//
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

/* Add a mesh to the mesh vector for rendering */
void Renderer::AddMesh(const std::string& name, const float* verticies, unsigned int numVerticies, 
                       const unsigned int* indicies, unsigned int numIndicies, const VertexBufferLayout& layout,
                       const std::string& shaderName, const std::vector<std::string>& textureNames)
{
    m_Meshes.push_back(std::make_unique<Mesh>(verticies, numVerticies, indicies, numIndicies, layout));
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

void Renderer::Cleanup() {
    glfwTerminate();
}
