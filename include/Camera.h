#pragma once

#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

/* Default camera values */
const glm::vec3 DefaultCameraPosition = { 0.0f, 0.0f, 3.f };
const glm::vec3 DefaultCameraUp = { .0f, .1f, .0f };
const float DefaultYaw = -90.f;
const float DefaultPitch = 0.f;
const float DefaultSpeed = 2.5f;
const float DefaultSensitivity = .1f;
const float DefaultZoom = 45.f;


class Camera
{
private:
    /*--- Camera Initis ---*/
    glm::vec3 m_CameraPosition;
    //glm::vec3 m_CameraTarget;
    glm::vec3 m_CameraFront; // direction camera is facing 
    // right axis
    glm::vec3 m_WorldUp; // true up vector relative to camera
    glm::vec3 m_CameraRight; // right vector relative to the camera
    // up axis
    glm::vec3 m_CameraUp;

    /*--- Utilitiy Vars ---*/
    float m_CameraSpeed = 1.0;
    float m_Sensitivity;
    float m_Yaw;
    float m_Pitch;
    float m_Zoom;
    bool m_ScrollZoomEnabled = true;
    
    /*--- Private functions ---*/
    void UpdateCameraVectors();

public:
    Camera(glm::vec3 position = DefaultCameraPosition, glm::vec3 up = DefaultCameraUp, float zoom = DefaultZoom, float yaw = DefaultYaw, float pitch = DefaultPitch);
    ~Camera();

    enum class CameraMovement {
        NONE = 0, FORWARD, BACKWARD, LEFT, RIGHT, UP, DOWN 
    };

    /*--- Setters  ---*/
    void SetCameraPosition(float direction);

    /*--- Getters ---*/
    float GetCameraSpeed() const { return m_CameraSpeed; }
    glm::vec3 GetPosition() const { return m_CameraPosition; }
    glm::vec3 GetFront() const { return m_CameraFront; }
    glm::mat4 GetViewMatrix() const;
    float GetYaw() const { return m_Yaw; }
    float GetPitch() const { return m_Pitch; }
    float GetZoom() const { return m_Zoom; }
    void EnableScrollZoom(bool enabled) { m_ScrollZoomEnabled = enabled;}
    bool IsScrollEnabled() const { return m_ScrollZoomEnabled; }

    /*--- Member Functions ---*/
    void ProcessKeyboardActions(CameraMovement direction, float deltaTime, float speedModifier = 1);
    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
    void ProcessMouseScroll(double yOffset);
};
