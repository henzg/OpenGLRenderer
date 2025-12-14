#include "Camera.h"
#include "glm/ext/quaternion_geometric.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include <unordered_map>

#include <iostream>

Camera::Camera(glm::vec3 position, glm::vec3 up, float zoom, float yaw, float pitch)
    : m_CameraPosition(position), m_WorldUp(up), m_Yaw(yaw), m_Pitch(pitch), m_Zoom(zoom), m_CameraFront(glm::vec3(0.0f, 0.0f, -1.0f))
{
    UpdateCameraVectors();
}

Camera::~Camera() {}

// glfw scroll control
void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
    xoffset *= m_Sensitivity;
    yoffset *= m_Sensitivity;

    m_Yaw   += xoffset;
    m_Pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (m_Pitch > 89.0f)
            m_Pitch = 89.0f;
        if (m_Pitch < -89.0f)
            m_Pitch = -89.0f;
    }

    // update Front, Right and Up Vectors using the updated Euler angles
    UpdateCameraVectors();
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
