#pragma once

//#include "Core.h"
#include "glm/glm.hpp"

class Camera
{
private:
    /*--- Camera Initis ---*/
    glm::vec3 m_CameraPosition;
    glm::vec3 m_CameraTarget;
    glm::vec3 m_CameraFront; // direction camera is facing 
    // right axis
    glm::vec3 m_WorldUp; // true up vector relative to camera
    glm::vec3 m_CameraRight; // right vector relative to the camera
    // up axis
    glm::vec3 m_CameraUp;

    /*--- Utilitiy Vars ---*/
    float m_CameraSpeed = 0.5f;
    
    /*--- Private functions ---*/
    void UpdateCameraVectors();

public:
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f));
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

    /*--- Member Functions ---*/
    void ProcessKeyboardActions(CameraMovement direction, float deltaTime, float speedModifier = 1);
};
