#pragma once

#include "Camera.h"
#include "GLFW/glfw3.h"

class InputManager
{
private:
    GLFWwindow* m_Window;
    Camera& m_Camera;
    bool m_FirstMouse = true;
    float m_LastX = 0.0f;
    float m_LastY = 0.0f;

public:
    InputManager(GLFWwindow* window, Camera& camera);
    ~InputManager() = default;

    void Update(float deltaTime);

    // Static callback for GLFW
    static void GlfwScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
    void ProcessMouseScroll(double yOffset);

private:
    // Mouse callback function
    static void MouseCallback(GLFWwindow* window, double xposIn, double yposIn);
    void ProcessMouseMovement(float xpos, float ypos);
};
