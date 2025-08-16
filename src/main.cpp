/* OpenGL Enditor
* Designed by Zachary Henry
 * Start of proj: Aug13,2025
 * Learning via learnopengl.com and the cherno
 */

#include "Window.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"
#include <iostream>

// register functions
void processInput(GLFWwindow* window);

float verticies[] =
    {
         0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

int main()
{
    Window window;
    VertexBuffer vbo(verticies, sizeof(verticies));
    Shader shaderProgram("../shaders/shader.vs", "../shaders/shader.fs");
    VertexArray vao;
    vao.AddBuffer(vbo);
    /*** --- Main loop --- ***/
    while(!window.shouldClose())
    {
        // input
        processInput(window.getNativeHandler());
        
        //render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shaderProgram.use();
        vao.Bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // check/call events and swap buffers
        window.swapBuffers();
        window.pollEvents();
    }
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
