#pragma once

#include "glad/glad.h"
#include "imgui/imgui.h"

#include "Window.h"
#include "ImGuiSystem.h"
#include "DeveloperWindow.h"
#include "Camera.h"
#include "tests/Test.h"

#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "VertexArray.h"
#include "GeometryData.h"

#include <vector>
#include <memory>
#include <map>
#include <string>

class Renderer
{
private:
    Window m_Window;
    ImGuiSystem m_ImGuiSystem;
    DeveloperWindow m_DevWindow;
    Camera m_Camera;

    float m_DeltaTime = 0.0f;
    float m_LastFrame = 0.0f;
    glm::vec3 m_DefaultWinColor = {0.2f, .3f, .3f};
    glm::vec3 m_CurrentWinColor;

    std::map<std::string, std::unique_ptr<VertexArray>> m_VAOs;
    std::map<std::string, std::unique_ptr<VertexBuffer>> m_VBOs;
    std::map<std::string, std::unique_ptr<Shader>> m_Shaders;
    std::map<std::string, std::unique_ptr<Mesh>> m_Meshes;
    std::map<std::string, std::unique_ptr<Texture>> m_Textures;

public:
    Renderer(const std::string& title, int width, int height);
    ~Renderer();
    
    /*Core functions*/
    void OnInit();
    void OnUpdate(float deltaTime);
    void OnRun(); //main loop
    void OnCleanup();
    void ProcessInput();

    /*Getters/Setters*/
    // RendererWindow
    int GetWindowWidth() const {return m_Window.getWidth();}
    int GetWindowHeight() const {return m_Window.getHeight();}
    glm::vec3 GetWindowDefaultColor() const {return m_DefaultWinColor;}

    void SetClearColor(float r, float g, float b);
    void SetClearColor(glm::vec3 color);
    void SetClearColor(ImVec4 color);

    float GetDeltaTime() const {return m_DeltaTime;}

    void EnableDepthTest(bool enabled) { enabled ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST); }
    /*-- Camera Manager Functions ----------------------------------------------------------*/
    glm::mat4 GetCameraViewMatrix() const { return m_Camera.GetViewMatrix(); }
    float GetCameraZoom() const { return m_Camera.GetZoom(); }
    glm::vec3 GetCameraPosition() const { return m_Camera.GetPosition(); }

    // RendererMeshes
    const Mesh* GetMesh(const std::string& name);
    int GetMeshesSize() const {return m_Meshes.size();}
    
    /*Add resources*/

    /*--- Vertex Array Manager Functions------------------------------------------------------------*/
    void AddVertexArray(const std::string& name);
    void ClearVertexArrays();
    VertexArray* GetVertexArray(const std::string& name);
    void BindVertexArray(const std::string& name);

    /*--- Vertex Buffer Manager Functions------------------------------------------------------------*/
    void AddVertexBuffer(const std::string& name, const void* data, unsigned int size);
    VertexBuffer* GetVertexBuffer(const std::string& name);
    void ClearVertexBuffers();

    /*--- Mesh Manager Functions------------------------------------------------------------*/
    void AddMesh(const std::string& name, const float* verticies, unsigned int numVerticies, 
                 const unsigned int* indicies, unsigned int numIndicies, const VertexBufferLayout& layout,
                 const std::string& shaderName, const std::vector<std::string>& textureNames);
    void AddMesh(const std::string& name, std::unique_ptr<Mesh> mesh);
    void ClearMeshes();

    /*-- Shader Manger Functions------------------------------------------------------------*/
    void AddShader(const std::string& name, const std::string& vsPath, const std::string& fsPath);
    Shader* GetShader(const std::string& name);
    void ClearShaders();
    
    /*--- Texture Manger Functions ---------------------------------------------------------*/
    void AddTexture(const std::string& name, const std::string& filePath, bool flip_on_load, bool hasRGBA);
    Texture* GetTexture(const std::string& name);
    //void RemoveTexture(const std::string& name);
    void ClearTextures()
    {
        m_Textures.clear();
    }

    bool ShouldClose() const;

    /*--- DevWindow Manager Functions-------------------------------------------------------*/
    template<typename T, typename... Args>
    void AddDevWindowWidget(Args&&... args)
    {
        m_DevWindow.AddWidget<T>(std::forward<Args>(args)...);
    }
    void RemoveDevWindowWidget(const std::string& label)
    {
        m_DevWindow.RemoveWidget(label);
    }
    void ClearDevWindowWidgets()
    {
        m_DevWindow.ClearWidgets();
    }

    void ToggleDevWindowWidget(const std::string& label)
    {
        m_DevWindow.ToggleWidget(label);
    }

    void EnableDevWindowWidget(const std::string& label)
    {
        m_DevWindow.EnableWidget(label);
    }

    void DisableDevWindowWidget(const std::string& label)
    {
        m_DevWindow.DisableWidget(label);
    }

    void TestRegister();
    
};
