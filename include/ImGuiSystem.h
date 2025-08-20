#pragma once
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>

class ImGuiSystem {
public:
    ImGuiSystem(GLFWwindow* window, bool enableDocking = true, bool enableViewports = false, const char* glsl_version = "#version 330");
    ~ImGuiSystem();

    void begin_frame();
    void end_frame();

private:
    GLFWwindow* m_Window;
    ImGuiContext* m_Context{nullptr};
    GLFWwindow* m_ViewportBackup;

};
