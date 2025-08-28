#include "Window.h"
#include <iostream>


Window::Window(const std::string& title, int width, int height)
    : m_Title(title) ,m_Width(width), m_Height(height)
{
    // 1) Init glfw window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);    
    
    // 2) create window object
    m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), NULL, NULL);
    if (m_Window == nullptr)
    {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(m_Window);
    
    // 3) initiate glad before we call opengl functions
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to init GLAD\n";
        glfwDestroyWindow(m_Window);
        glfwTerminate();
        throw std::runtime_error("Failed to initilize glad");
    }

    //glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // 4) viewport
    glViewport(0,0,m_Width,m_Height);
}

Window::~Window()
{
    glfwDestroyWindow(m_Window);
}

