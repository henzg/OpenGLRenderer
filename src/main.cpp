/* OpenGL Enditor
* Designed by Zachary Henry
 * Start of proj: Aug13,2025
 * Learning via learnopengl.com and the cherno
 */

#include "Window.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "stb_image.h"
#include "ImGuiSystem.h"
#include "DeveloperWindow.h"

#include <iostream>

// register functions
void processInput(GLFWwindow* window);
float texvis = .02f;

// some data used throughout for testing purposes
float verticies[] =
    {
         -0.5f,  -0.5f,    // 0
          0.5f,  -0.5f,  //  1
          0.5f,   0.5f, //   2
         -0.5f,   0.5f,//    3
         
    };

float verticiesWithColor[] =
    {
         -0.5f,  -0.5f, 1.0f, 0.0f, 0.0f,  // 0
          0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, //  1
          0.5f,   0.5f, 0.0f, 0.0f, 1.0f,//   2
         -0.5f,   0.5f, .25f, .25f, .25f//    3
         
    };

float verticiesWithTexCords[] =
    {
         -0.5f,  -0.5f, 1.0f, 0.0f, 0.0f, 0.0f,  0.0f,  // 0
          0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 1.0f,  0.0f, //  1
          0.5f,   0.5f, 0.0f, 0.0f, 1.0f, 1.0f,  1.0f,//   2
         -0.5f,   0.5f, .25f, .25f, .25f, 0.0f, 1.0f//    3
         
    };

float twoTriangles[] =
    {
        // tri angle one
        1.f, -.5f, 0.0f,
        .5f, -.5f, 0.0f,
        .75f, .5f, 0.0f,
        // triangle two
        -1.f, -.5f, 0.0f,
        -.5f, -.5f, 0.0f,
        -.75f, .5f, 0.0f
    };

float triangleOne[] =
    {
        0.f, -0.5f, 0.f,
        -.9f, -.5f, 0.f,
        -.45f, .5f, 0.f
    };
float triangleTwo[] = 
    {
        .9f, -.5f, 0.f,
        .0f, -.5f, 0.f,
        .45f, .5f, 0.f
    };

unsigned int indicies[]
{
    0,1,2,
    2,3,0
};

int main()
{
    Window window;
    
    VertexArray va;
    VertexBuffer vb(verticiesWithTexCords, 7 * 4 * sizeof(float));
    
    VertexBufferLayout layout = {
        {ShaderDataType::Float2, "a_Position"},
        {ShaderDataType::Float3, "a_Color"},
        {ShaderDataType::Float2, "textCords"}
    };
    
    Shader shaderProgram("../shaders/texshader.vs", "../shaders/texShader.fs");
    
    va.AddBuffer(vb, layout);
    IndexBuffer ib(indicies, 6); 
    
    /*--- Texture Loading ---*/
    unsigned int texture1, texture2;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    
     // texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
     // texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* texdata = stbi_load("../res/wood.png", &width, &height, &nrChannels, 0);

    if (texdata)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texdata);
        glGenerateMipmap(GL_TEXTURE_2D);
        std::cout << "IMAGE::LOAD::SUCCESS::TEXTURE\n";
    }
    else 
    {
        std::cout << "IMAGE::LOAD::FAILED::TEXTURE\n";
    }
    stbi_image_free(texdata);
    
    // texture 2 loading 
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    
     // texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
     // texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_set_flip_vertically_on_load(true);
    texdata = stbi_load("../res/awesomeface.png", &width, &height, &nrChannels, 0);
    if (texdata)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texdata);
        glGenerateMipmap(GL_TEXTURE_2D);
        std::cout << "IMAGE::LOAD02::SUCCESS::TEXTURE\n";
    }
    else 
    {
        std::cout << "IMAGE::LOAD02::FAILED::TEXTURE\n";
    }
    stbi_image_free(texdata);

    shaderProgram.use();
    shaderProgram.setInt("texture1", 0);
    shaderProgram.setInt("texture2", 1);
    shaderProgram.setFloat("texvis", texvis);

    /*--- IMGUI ---*/
    ImGuiSystem imguisys(window.getNativeHandler());
    DeveloperWindow devwin("zacstack.dev", ImVec2(100, 100), ImVec2(400,300));
    devwin.BindFloat("Mix Amount", &texvis, 0.0f, 1.0f);


    /*** --- Main loop --- ***/
    while(!window.shouldClose())
    {
        // input
        processInput(window.getNativeHandler());
        
        //render - clear color to something, then use a shader program then bind buffers then draw
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        
        shaderProgram.use();
        shaderProgram.setFloat("texvis", texvis);
        va.Bind();
        ib.Bind();
        
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        imguisys.begin_frame();
        devwin.Draw();
        imguisys.end_frame();
        
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
    else if(glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    {
        texvis += 0.01f;
        if(texvis >= 1.0f )
            texvis = 1.0f;
        std::cout << texvis << "\n";
    }
    else if(glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    {
        texvis -= 0.01f;
        if(texvis <= 0.0f )
            texvis = 0.0f;
        std::cout << texvis << "\n";

    }
}
