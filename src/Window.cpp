#include "Window.h"
#include "Core.h"
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    Window* windowPtr = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if(windowPtr)
    {
        windowPtr->setDimensions(width, height);
    }
    GLCall(glViewport(0,0,width,height));
}

Window::Window(const std::string& title, int width, int height)
    : m_Title(title) ,m_Width(width), m_Height(height)
{
    // 1) Init glfw window
    GLCall(glfwInit());
    GLCall(glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3));
    GLCall(glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3));
    GLCall(glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE));    
    
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

    glfwSetWindowUserPointer(m_Window, this);
    glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);

    // 4) initial viewport
    glViewport(0,0,m_Width,m_Height);
}

Window::~Window()
{
    glfwDestroyWindow(m_Window);
}

void Window::setDimensions(int width, int height)
{
    m_Width = width;
    m_Height = height;
}

