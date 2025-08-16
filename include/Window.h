#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"

class Window
{
public:

    Window();
    ~Window();

    void pollEvents() const { glfwPollEvents(); }
    void swapBuffers() const { glfwSwapBuffers(m_window); }
    bool shouldClose() const { return glfwWindowShouldClose(m_window); }
    GLFWwindow* getNativeHandler() const { return m_window; }

private:
    unsigned int m_width = 0, m_height = 0;
    GLFWwindow* m_window = nullptr;
};
