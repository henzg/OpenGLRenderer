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
    ImVec4 m_WinColor = {0.2f, 0.3f, 0.3f, 1.0f};

    std::map<std::string, std::unique_ptr<Shader>> m_Shaders;
    std::vector<std::unique_ptr<Mesh>> m_Meshes;
    std::map<std::string, std::unique_ptr<Texture>> m_Textures;

public:
    Renderer(const std::string& title, int width, int height);
    ~Renderer();
    /*Core functions*/
    void Init();
    void OnUpdate(float deltaTime);
    void Run(); //main loop
    void Cleanup();
    void ProcessInput();

    /*Getters/Setters*/
    // RendererWindow
    int GetWindowWidth() const {return m_Window.getWidth();}
    int GetWindowHeight() const {return m_Window.getHeight();}
    ImVec4 GetWindowDefaultColor() const {return m_WinColor;}
    float GetDeltaTime() const {return m_DeltaTime;}

    // RendererCamera
    glm::mat4 GetCameraViewMatrix() const {return m_Camera.GetViewMatrix();}

    // RendererMeshes
    const std::vector<std::unique_ptr<Mesh>>& GetMeshes() const { return m_Meshes; }
    int GetMeshesSize() const {return m_Meshes.size();}
    
    /*Add resources*/
    void AddMesh(const std::string& name, const float* verticies, unsigned int numVerticies, 
                 const unsigned int* indicies, unsigned int numIndicies, const VertexBufferLayout& layout,
                 const std::string& shaderName, const std::vector<std::string>& textureNames);
    void ClearMeshes();

    void AddShader(const std::string& name, const std::string& vsPath, const std::string& fsPath);
    Shader* GetShader(const std::string& name);

    void AddTexture(const std::string& name, const std::string& filePath, bool flip_on_load, bool hasRGBA);
    Texture* GetTexture(const std::string& name);

    bool ShouldClose() const;

    template<typename T, typename... Args>
    void AddDevWindowWidget(Args&&... args)
    {
        m_DevWindow.AddWidget<T>(std::forward<Args>(args)...);
    }
    void RemoveDevWindowWidget(const std::string& label)
    {
        m_DevWindow.RemoveWidget(label);
    }
    void ClearDevWindowWidget()
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
};
