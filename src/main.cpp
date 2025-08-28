/* OpenGL Enditor
* Designed by Zachary Henry
 * Start of proj: Aug13,2025
 * Learning via learnopengl.com and the cherno
 */
#include "Renderer.h"

// register functions
//void mouse_callback(GLFWwindow*, double xpos, double ypos);


/* -- Camera Variabls -- */
/* glm::vec3 sceneOrigin = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f); // positive z is coming towards me
glm::vec3 cameraTarget = glm::vec3(sceneOrigin);
glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget); // note camera is actually pointing in reverse direction of what it is targeting
glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

bool firstMouse = true;
float yaw = -90.f;
float pitch = 0.0f;
float lastX = 800.0f / 2.0f;
float lastY = 600.0f / 2.0f;

float deltaTime = 0.0f;
float lastFrame = 0.0f;
*/

int main()
{
    try 
    {
        const std::string myTitle = "zacstack.dev";
        Renderer program(myTitle, 800, 600);
        program.Init();
        program.Run();
        program.Cleanup();
    } 
    catch (const std::runtime_error& e)
    {
        std::cerr << "Renderer init failed: " << e.what() << "\n";
        return -1;
    }

    return 0;
}
    /*--- transformations ---*/
    //unsigned int transformLoc = glGetUniformLocation(shaderProgram.getShaderId(), "transform");
    //glEnable(GL_DEPTH_TEST);

    /*--- Moust movement ---*/
    //glfwSetCursorPosCallback(window.getNativeHandler(), mouse_callback);    
    
    /*** --- Main loop --- ***/
    /*
    while(!window.shouldClose())
    {
        // per-frame logic
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        
        // pass projection matrix
        glm::mat4 projection = glm::perspective(glm::radians(fov), window.getWidth() / window.getHeight(), 0.1f, 100.0f);
        shaderProgram.setMat4("projection", projection);

        // set view
        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        shaderProgram.setMat4("view", view);

        // Build cubes
        va.Bind();
        ib.Bind();
        for(unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * 1;
            if (i % 3 == 0)
                angle = 25.0 * (float)glfwGetTime();
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            shaderProgram.setMat4("model", model);

            glDrawElements(GL_TRIANGLES, sizeof(cubeIndicies) / sizeof(unsigned int), GL_UNSIGNED_INT, nullptr);

        }
        */
/*
void processInput(GLFWwindow* window)
{
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    float cameraSpeed = .015f * deltaTime;

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

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    float xoffset = xpos - lastX;
    float yoffset = ypos - lastY;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.05f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}
*/
