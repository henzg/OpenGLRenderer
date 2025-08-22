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
#include "ext/matrix_transform.hpp"
#include "stb_image.h"
#include "ImGuiSystem.h"
#include "DeveloperWindow.h"
#include "ImguiWidget.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"


#include <iostream>

// register functions
void processInput(GLFWwindow* window);

/* --- global variables, used for imgui widgets mostly --- */
float texvis = .02f;
ImVec4 winColor = {0.0f, 0.0f, 0.0f, 1.0f };
float rotateAmount = 90.0f;
float fov = 90.0f;
glm::vec3 containerPos = {-2.0f, 0.5f, -2.8f};

/* -- Camera Variabls -- */
glm::vec3 sceneOrigin = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f); // positive z is coming towards me
glm::vec3 cameraTarget = glm::vec3(sceneOrigin);
glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget); // note camera is actually pointing in reverse direction of what it is targeting
glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

//glm::mat4 view;
//view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
//                   glm::vec3(0.0f, 0.0f, 0.0f),
//                   glm::vec3(0.0f, 1.0f, 0.0f));

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
// 2f = pos, 3f = colour, 2f = texcords
float verticiesWithTexCords[] =
    {
         -0.5f,  -0.5f, 1.0f, 0.0f, 0.0f, 0.0f,  0.0f,  // 0
          0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 1.0f,  0.0f, //  1
          0.5f,   0.5f, 0.0f, 0.0f, 1.0f, 1.0f,  1.0f,//   2
         -0.5f,   0.5f, .25f, .25f, .25f, 0.0f, 1.0f//    3
         
    };
float verticiesWithTexCords2[] =
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

float cubeverticies[] =
    {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

glm::vec3 cubePositions[] =
{
    glm::vec3( 0.0f, 0.0f, 0.0f),
    glm::vec3( 2.0f, 5.0f, -15.0f),
    glm::vec3( -1.5f, -2.2f, -2.5f),
    glm::vec3( -3.8f, -2.0f, -12.3f),
    glm::vec3( 2.4f, -0.4f, -3.5f),
    glm::vec3( -1.7f, 3.0f, -7.5f),
    glm::vec3( 1.3f, -2.0f, -2.5f),
    glm::vec3( 1.5f, 2.0f, -2.5f),
    glm::vec3( 1.5f, 0.2f, -1.5f),
    glm::vec3( -1.3f, 1.0f, -1.5f),
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
    VertexBuffer vb(cubeverticies, sizeof(cubeverticies));

    VertexBufferLayout layout = {
        {ShaderDataType::Float3, "a_Position"},
        {ShaderDataType::Float2, "textCords"}
    };
    
    Shader shaderProgram("../shaders/texshader.vs", "../shaders/texshader.fs");
    
    va.AddBuffer(vb, layout);
    //IndexBuffer ib(indicies, 36); 
    
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
    DeveloperWindow devwin("zacstack.dev", ImVec2(800, 800), ImVec2(700,800));
    devwin.AddWidget<ImguiSliderFloat>("Mix Value", &texvis, 0.0f, 1.0f);
    devwin.AddWidget<ImguiSliderFloat>("FOV", &fov, 10.0f, 180.0f);
    devwin.AddWidget<ImguiColorPicker4>("Clear COlor", &winColor, true);
    devwin.AddWidget<ImguiDragFloat3>("Position", &containerPos, 0.01f);
    /*--- transformations ---*/
    unsigned int transformLoc = glGetUniformLocation(shaderProgram.ID, "transform");
    glEnable(GL_DEPTH_TEST);
    
    /*** --- Main loop --- ***/
    while(!window.shouldClose())
    {
        // input
        processInput(window.getNativeHandler());
        
        //render - clear color to something, then use a shader program then bind buffers then draw
        glClearColor(winColor.x, winColor.y, winColor.z, winColor.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
      
        /* activate shader */
        shaderProgram.use();
        shaderProgram.setFloat("texvis", texvis);
        
        // camera
        const float radius = 10.0f;
        glm::mat4 view = glm::mat4(1.0f);
        float camX = static_cast<float>(sin(glfwGetTime()) * radius);
        float camZ = static_cast<float>(cos(glfwGetTime()) * radius);
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        shaderProgram.setMat4("view", view);

        va.Bind();
        //ib.Bind();
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        for(unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            //glm::mat4 view          = glm::mat4(1.0f);
            glm::mat4 projection    = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * 1;
            if (i % 3 == 0)
                angle = 25.0 * (float)glfwGetTime();
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            //view    = glm::translate(view, glm::vec3(containerPos.x, containerPos.y, containerPos.z));
            projection = glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f);
            shaderProgram.setMat4("model", model);
            //shaderProgram.setMat4("view", view);
            shaderProgram.setMat4("projection", projection);

            glDrawArrays(GL_TRIANGLES, 0, 36);

        }


        /* imgui | devwindow */
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
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    float cameraSpeed = .15f * deltaTime;

    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if(glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    {
        texvis += 0.01f;
        if(texvis >= 1.0f )
            texvis = 1.0f;
        std::cout << texvis << "\n";
    }
    if(glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    {
        texvis -= 0.01f;
        if(texvis <= 0.0f )
            texvis = 0.0f;
        std::cout << texvis << "\n";

    }
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}
