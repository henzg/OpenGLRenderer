#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <string>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);

class Window
{
public:

    Window(const std::string& title, int width, int height);
    ~Window();

    void pollEvents() const { glfwPollEvents(); }
    void swapBuffers() const { glfwSwapBuffers(m_Window); }
    bool shouldClose() const { return glfwWindowShouldClose(m_Window); }
    
    GLFWwindow* getNativeHandler() const { return m_Window; }
    int getWidth() const { return m_Width; }
    int getHeight() const { return m_Height; }

    void setDimensions(int width, int height);

private:
    std::string m_Title;
    unsigned int m_Width = 0, m_Height = 0;
    GLFWwindow* m_Window = nullptr;
};
