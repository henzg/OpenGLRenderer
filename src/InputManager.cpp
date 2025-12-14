#include "InputManager.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include <iostream>
#include <unordered_map>

namespace {
    // Static map to associate GLFW window pointers with InputManager instances
    std::unordered_map<GLFWwindow*, InputManager*>& windowToInputManager() {
        static std::unordered_map<GLFWwindow*, InputManager*> map;
        return map;
    }
}

InputManager::InputManager(GLFWwindow* window, Camera& camera)
    : m_Window(window), m_Camera(camera)
{
    windowToInputManager()[m_Window] = this;
    glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void InputManager::Update(float deltaTime)
{
    // Skip input processing if ImGui is capturing mouse or keyboard
    if (ImGui::GetIO().WantCaptureMouse || ImGui::GetIO().WantCaptureKeyboard)
    {
        return;
    }

    double xposIn, yposIn;
    glfwGetCursorPos(m_Window, &xposIn, &yposIn);

    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (m_FirstMouse)
    {
        m_LastX = xpos;
        m_LastY = ypos;
        m_FirstMouse = false;
    }

    float xoffset = xpos - m_LastX;
    float yoffset = m_LastY - ypos; // reversed since y-coordinates go from bottom to top

    m_LastX = xpos;
    m_LastY = ypos;

    m_Camera.ProcessMouseMovement(xoffset, yoffset);
    if(glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_Window, true);

    if(glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS)
        m_Camera.ProcessKeyboardActions(Camera::CameraMovement::FORWARD, deltaTime);
    if(glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS)
        m_Camera.ProcessKeyboardActions(Camera::CameraMovement::BACKWARD, deltaTime);
    if(glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS)
        m_Camera.ProcessKeyboardActions(Camera::CameraMovement::LEFT, deltaTime);
    if(glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS)
        m_Camera.ProcessKeyboardActions(Camera::CameraMovement::RIGHT, deltaTime);
    if(glfwGetKey(m_Window, GLFW_KEY_SPACE) == GLFW_PRESS)
        m_Camera.ProcessKeyboardActions(Camera::CameraMovement::UP, deltaTime);
    if(glfwGetKey(m_Window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        m_Camera.ProcessKeyboardActions(Camera::CameraMovement::DOWN, deltaTime);
}
