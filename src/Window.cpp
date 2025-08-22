#include "Window.h"
#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

Window::Window()
    : m_width(1000), m_height(850)
{
    // 1) Init glfw window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);    

    // 2) create window object
    m_window = glfwCreateWindow(m_width, m_height, "Zacstack.dev", NULL, NULL);
    if (m_window == nullptr)
    {
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
    }
    glfwMakeContextCurrent(m_window);
    
    // 3) initiate glad before we call opengl functions
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to init GLAD" << std::endl;
    }

    // 4) viewport
    glViewport(0,0,m_width,m_height);
}

Window::~Window()
{
    glfwDestroyWindow(m_window);
}

