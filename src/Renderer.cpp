#include "Renderer.h"

#include "Core.h"
#include "Data.h"
#include "Settings.h"
#include "glm/ext/matrix_transform.hpp"
#include <GLFW/glfw3.h>

Renderer::Renderer(const std::string& title, int width, int height)
    : m_Window(title, width, height), 
      m_ImGuiSystem(m_Window.getNativeHandler()),
      m_DevWindow(title, ImVec2(800,800), ImVec2(700,800))
{}

Renderer::~Renderer() {}

void Renderer::Init() 
{
    glEnable(GL_DEPTH_TEST);
    
    m_DevWindow.AddWidget<ImguiSliderFloat>("Mix Value", &m_TexVis, 0.0f, 1.0f);
    m_DevWindow.AddWidget<ImguiSliderFloat>("FOV", &m_Fov, 10.0f, 180.0f);
    m_DevWindow.AddWidget<ImguiColorPicker4>("Clear COlor", &m_WinColor, true);

    /*Add shaders*/
    AddShader("texShader", "../shaders/texshader.vs", "../shaders/texshader.fs");
    Shader* texShader = GetShader("texShader");
    if (texShader)
    {
        texShader->use();
        texShader->setInt("texture1", 0);
        texShader->setInt("texture2", 1);
    }

    /*Add Textures*/
    AddTexture("woodTex", "../res/wood.png", false, false);
    AddTexture("awesomeFace", "../res/awesomeface.png", true, true);

    /*Add Meshes*/
    VertexBufferLayout cubeLayout = {
        {ShaderDataType::Float3, "a_Position"},
        {ShaderDataType::Float2, "textCords"}
    };

    AddMesh("mainCube", cubeverticies, sizeof(cubeverticies) / (5 * sizeof(float)), 
            cubeIndicies, sizeof(cubeIndicies) / sizeof(unsigned int),
           cubeLayout, "texShader", {"woodTex", "awesomeFace"});
}

void Renderer::Run() {
   while (!ShouldClose())
    {
        // per-frame logic
        float currentFrame = static_cast<float>(glfwGetTime());
        m_DeltaTime = currentFrame - m_LastFrame;
        m_LastFrame = currentFrame;

        ProcessInput();

        glClearColor(m_WinColor.x, m_WinColor.y, m_WinColor.z, m_WinColor.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
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
            glm::mat4 view = glm::lookAt(glm::vec3 (0.f,0.f,3.f), /*camea position*/ 
                                         glm::vec3 (0.f,0.f,0.f), /*look at origin*/ 
                                         glm::vec3(0.f,1.f,0.f)); /*up vector*/
            currentShader->setMat4("view", view);

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
        
        // imgui
        m_ImGuiSystem.begin_frame();
        m_DevWindow.Draw();
        m_ImGuiSystem.end_frame();

        // swap buffers and pollevents
        m_Window.swapBuffers();
        m_Window.pollEvents();
    }
}

bool Renderer::ShouldClose() const 
{
    return m_Window.shouldClose();
}

void Renderer::AddMesh(const std::string& name, const float* verticies, unsigned int numVerticies, 
                       const unsigned int* indicies, unsigned int numIndicies, const VertexBufferLayout& layout,
                       const std::string& shaderName, const std::vector<std::string>& textureNames)
{
    m_Meshes.push_back(std::make_unique<Mesh>(verticies, numVerticies, indicies, numIndicies, layout));
}

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
}

void Renderer::Cleanup() {
    glfwTerminate();
}
