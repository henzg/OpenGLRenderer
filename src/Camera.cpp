#include "Camera.h"
#include "glm/ext/quaternion_geometric.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <iostream>

Camera::Camera(glm::vec3 position, glm::vec3 up, float zoom)
    : m_CameraPosition(position), m_CameraFront(glm::vec3(0.0f, 0.0f, -1.0f)), m_WorldUp(up), m_Zoom(zoom)
{
    UpdateCameraVectors();
}

Camera::~Camera() {}

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

void Camera::ProcessMouseScroll(float yoffset)
{
    m_Zoom -= (float)yoffset;
    if (m_Zoom < 1.0f)
        m_Zoom = 1.0f;
    if (m_Zoom > 45.0f)
        m_Zoom = 45.0f;
}
