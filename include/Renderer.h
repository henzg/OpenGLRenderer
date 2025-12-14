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
#include "Scene.h" // Include Scene.h
#include "InputManager.h" // Include InputManager.h

#include <string>
#include <memory>
#include "ResourceManager.h" // Include the new resource manager

class Renderer
{
private:
    Window m_Window;
    ImGuiSystem m_ImGuiSystem;
    DeveloperWindow m_DevWindow;
    Camera m_Camera;
    ResourceManager m_ResourceManager; // Instance of the new resource manager
    Scene m_Scene; // Instance of the scene
    InputManager m_InputManager; // Instance of the Input Manager

    float m_DeltaTime = 0.0f;
    float m_LastFrame = 0.0f;
    glm::vec3 m_DefaultWinColor = {0.2f, .3f, .3f};
    glm::vec3 m_CurrentWinColor;

public:
    Renderer(const std::string& title, int width, int height);
    ~Renderer();
    
    /*Core functions*/
    void OnInit();
    void OnUpdate(float deltaTime);
    void OnRun(); //main loop
    void OnRender(Scene& scene);
    void OnCleanup();

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

    /*--- Resource Manager Accessors -------------------------------------------------------*/
    ResourceManager& GetResourceManager() { return m_ResourceManager; }
    const ResourceManager& GetResourceManager() const { return m_ResourceManager; }

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
    InputManager& GetInputManager() { return m_InputManager; }

    /*--- ImGuiSystem Accessors ------------------------------------------------------------*/
    ImGuiSystem& GetImGuiSystem() { return m_ImGuiSystem; }
    const ImGuiSystem& GetImGuiSystem() const { return m_ImGuiSystem; }

    /*--- DeveloperWindow Accessors --------------------------------------------------------*/
    DeveloperWindow& GetDevWindow() { return m_DevWindow; }
    const DeveloperWindow& GetDevWindow() const { return m_DevWindow; }

    /*--- Window Accessors -----------------------------------------------------------------*/
    Window& GetWindow() { return m_Window; }
    const Window& GetWindow() const { return m_Window; }

    void TestRegister();
    
};
