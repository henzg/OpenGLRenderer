#include "Camera.h"
#include "glm/ext/quaternion_geometric.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include <unordered_map>

#include <iostream>

Camera::Camera(glm::vec3 position, glm::vec3 up, float zoom)
    : m_CameraPosition(position), m_CameraFront(glm::vec3(0.0f, 0.0f, -1.0f)), m_WorldUp(up), m_Zoom(zoom)
{
    UpdateCameraVectors();
}

Camera::~Camera() {}

// glfw scroll control
namespace {
    std::unordered_map<GLFWwindow*, Camera*>& windowToCamera() {
    static std::unordered_map<GLFWwindow*, Camera*> map;
    return map;
    }
}

void Camera::AttachToWindow(GLFWwindow* window) {
    windowToCamera()[window] = this;
    glfwSetScrollCallback(window, Camera::GlfwScrollCallback);
}

void Camera::DetachFromWindow(GLFWwindow* window) {
    windowToCamera().erase(window);
}

void Camera::GlfwScrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
    // preserve imgui
    ImGui_ImplGlfw_ScrollCallback(window, xOffset, yOffset);
    // dont zoom while hovering widget
    if(ImGui::GetCurrentContext() && ImGui::GetIO().WantCaptureMouse)
        return;

    auto it = windowToCamera().find(window);
    if(it == windowToCamera().end())
        return;

    Camera* cam = it->second;
    if (!cam || !cam->IsScrollEnabled())
        return;

    cam->ProcessMouseScroll(static_cast<float>(yOffset));
        
}

void Camera::UpdateCameraVectors()
{
    m_CameraRight = glm::normalize(glm::cross(m_CameraFront, m_WorldUp));
    m_CameraUp = glm::normalize(glm::cross(m_CameraRight, m_CameraFront));
}

glm::mat4 Camera::GetViewMatrix() const 
{
    return glm::lookAt(m_CameraPosition, m_CameraPosition + m_CameraFront, m_CameraUp);
}

void Camera::ProcessKeyboardActions(CameraMovement direction, float deltaTime, float speedModifier)
{
   float velocity = speedModifier * (m_CameraSpeed * deltaTime);

    switch (direction)
    {
        case CameraMovement::FORWARD:
            m_CameraPosition += m_CameraFront * velocity;
            break;
        case CameraMovement::BACKWARD:
            m_CameraPosition -= m_CameraFront * velocity;
            break;
        case CameraMovement::LEFT:
            m_CameraPosition -= m_CameraRight * velocity;
            break;
        case CameraMovement::RIGHT:
            m_CameraPosition += m_CameraRight * velocity;
            break;
        case CameraMovement::UP:
            m_CameraPosition += m_CameraUp * velocity;
            break;
        case CameraMovement::DOWN:
            m_CameraPosition -= m_CameraUp * velocity;
            break;
    }
    
}

void Camera::ProcessMouseScroll(double yOffset)
{
    m_Zoom -= (float)yOffset;
    if (m_Zoom < 1.0f)
        m_Zoom = 1.0f;
    if (m_Zoom > 100.0f)
        m_Zoom = 100.0f;
}
