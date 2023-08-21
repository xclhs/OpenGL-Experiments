#define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "shader.h"
#include "objLoader.h"
#include "camera.h"
#include "stb_image.h"

#include <iostream>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void running();
unsigned int loadTexture(const char *path);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


camera c(glm::vec3(2.0f,2.0f,10.0f));
bool firstMouse = true;
float lastX =  800.0f / 2.0;
float lastY =  600.0 / 2.0;
bool Click=false;
float speed=0;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;
float diffuse=0.5f,ambient=0.2f;



int main()
{
    objLoader o,o1;
    o.readFile("F:\\C\\graph\\final\\source\\puget_tex.obj");
    o1.readFile("F:\\C\\graph\\final\\source\\camel.obj");


    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetMouseButtonCallback(window,mouse_button_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glEnable(GL_DEPTH_TEST);


    shader s("F:\\C\\graph\\final\\shader\\vertex.glsl","F:\\C\\graph\\final\\shader\\fragment.glsl");
    shader obj("F:\\C\\graph\\final\\shader\\obj_vs.glsl","F:\\C\\graph\\final\\shader\\obj_fs.glsl");
    shader light("F:\\C\\graph\\final\\shader\\light_vs.glsl","F:\\C\\graph\\final\\shader\\light_fs.glsl");
    float vertices[] = {
            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f,  0.5f, -0.5f,
            0.5f,  0.5f, -0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f, -0.5f,  0.5f,
            0.5f, -0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,

            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,

            0.5f,  0.5f,  0.5f,
            0.5f,  0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,

            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f,  0.5f,
            0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f,  0.5f, -0.5f,
            0.5f,  0.5f, -0.5f,
            0.5f,  0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f,
    };

    glm::vec3 pointLightPositions[] = {
            glm::vec3( 32.0f,  3.0f,  32.0f),
            glm::vec3( 32.0f, 3.0f, 0.0f),
            glm::vec3(0.0f,  3.0f, 32.0f),
            glm::vec3( 0.0f,  3.0f, 0.0f)
    };

    unsigned int VBO[3], VAO[3],EBO[3];
    glGenVertexArrays(3, VAO);
    glGenBuffers(3, VBO);
    glGenBuffers(3, EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).

    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, o.V.size()*sizeof(vertex), &(o.V[0]), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,o.S.size()*sizeof(unsigned int),&(o.S[0]),GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)(0));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)(offsetof(vertex,normal)));
    glEnableVertexAttribArray(1);

    // color attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,  sizeof(vertex), (void*)(offsetof(vertex,texture)));
    glEnableVertexAttribArray(2);


    unsigned int texture1 = loadTexture("F:\\C\\graph\\final\\source\\puget_tex.png");
    s.use();
    s.setInt("material.diffuse",0);

    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, o1.V.size()*sizeof(vertex), &(o1.V[0]), GL_STATIC_DRAW);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,o1.S.size()*sizeof(unsigned int),&(o1.S[0]),GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)(0));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)(offsetof(vertex,normal)));
    glEnableVertexAttribArray(1);

    obj.use();
    glm::vec3 lightColor=glm::vec3(0.8f,0.8f,0.4f);
    glm::vec3 diffuseColor = lightColor   * glm::vec3(diffuse); // decrease the influence
    glm::vec3 ambientColor = diffuseColor * glm::vec3(ambient); // low influence
    /*
     * 素材可控修改此值
     * */
    obj.setVec3("material.diffuse",diffuseColor);
    obj.setVec3("material.ambient",ambientColor);
    obj.setVec3("material.specular", 0.5f, 0.5f, 0.5f);


    glBindVertexArray(VAO[2]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        s.use();
        s.setVec3("viewPos", c.Position);
        s.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
        s.setFloat("material.shininess", 32.0f);

        s.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
        s.setVec3("dirLight.ambient", 0.01f, 0.01f, 0.01f);
        s.setVec3("dirLight.diffuse", 0.2f, 0.2f, 0.2f);
        s.setVec3("dirLight.specular", 0.05f, 0.05f, 0.05f);

        //point light 1
        s.setVec3("pointLights[0].position", pointLightPositions[0]);
        s.setVec3("pointLights[0].ambient", 0.1f, 0.1f, 0.1f);
        s.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
        s.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
        s.setFloat("pointLights[0].constant", 1.0f);
        s.setFloat("pointLights[0].linear", 0.09);
        s.setFloat("pointLights[0].quadratic", 0.032);

        // point light 2
        s.setVec3("pointLights[1].position", pointLightPositions[1]);
        s.setVec3("pointLights[1].ambient", 0.1f, 0.1f, 0.1f);
        s.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
        s.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
        s.setFloat("pointLights[1].constant", 1.0f);
        s.setFloat("pointLights[1].linear", 0.09);
        s.setFloat("pointLights[1].quadratic", 0.032);

        // point light 3
        s.setVec3("pointLights[2].position", pointLightPositions[2]);
        s.setVec3("pointLights[2].ambient", 0.1f, 0.1f, 0.1f);
        s.setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
        s.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
        s.setFloat("pointLights[2].constant", 1.0f);
        s.setFloat("pointLights[2].linear", 0.09);
        s.setFloat("pointLights[2].quadratic", 0.032);
        // point light 4
        s.setVec3("pointLights[3].position", pointLightPositions[3]);
        s.setVec3("pointLights[3].ambient", 0.1f, 0.1f, 0.1f);
        s.setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
        s.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
        s.setFloat("pointLights[3].constant", 1.0f);
        s.setFloat("pointLights[3].linear", 0.09);
        s.setFloat("pointLights[3].quadratic", 0.032);
        // spotLight
        s.setVec3("spotLight.position", c.Position);
        s.setVec3("spotLight.direction", c.Front);
        s.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
        s.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
        s.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
        s.setFloat("spotLight.constant", 1.0f);
        s.setFloat("spotLight.linear", 0.09);
        s.setFloat("spotLight.quadratic", 0.032);
        s.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
        s.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

        glm::mat4 model         = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 view          = glm::lookAt(c.Position,c.Position+c.Front,c.Up);
        glm::mat4 projection    = glm::perspective(glm::radians(c.Zoom),(float)SCR_WIDTH/SCR_HEIGHT,0.1f,100.0f);

        s.setMat4("view",view);
        s.setMat4("model",model);
        s.setMat4("projection",projection);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,texture1 );
        glBindVertexArray(VAO[0]);
        glDrawElements(GL_TRIANGLES,o.S.size(), GL_UNSIGNED_INT, 0);

        obj.use();
        diffuseColor = lightColor   * glm::vec3(diffuse); // decrease the influence
        ambientColor = diffuseColor * glm::vec3(ambient); // low influence
        obj.setVec3("material.diffuse",diffuseColor);
        obj.setVec3("material.ambient",ambientColor);
        obj.setVec3("viewPos", c.Position);
        obj.setFloat("material.shininess", 32.0f);

        obj.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
        obj.setVec3("dirLight.ambient", 0.01f, 0.01f, 0.01f);
        obj.setVec3("dirLight.diffuse", 0.2f, 0.2f, 0.2f);
        obj.setVec3("dirLight.specular", 0.05f, 0.05f, 0.05f);

        //point light 1
        obj.setVec3("pointLights[0].position", pointLightPositions[0]);
        obj.setVec3("pointLights[0].ambient", 0.10f, 0.1f, 0.1f);
        obj.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
        obj.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
        obj.setFloat("pointLights[0].constant", 1.0f);
        obj.setFloat("pointLights[0].linear", 0.09);
        obj.setFloat("pointLights[0].quadratic", 0.032);

        // point light 2
        obj.setVec3("pointLights[1].position", pointLightPositions[1]);
        obj.setVec3("pointLights[1].ambient", 0.1f, 0.1f, 0.1f);
        obj.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
        obj.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
        obj.setFloat("pointLights[1].constant", 1.0f);
        obj.setFloat("pointLights[1].linear", 0.09);
        obj.setFloat("pointLights[1].quadratic", 0.032);

        // point light 3
        obj.setVec3("pointLights[2].position", pointLightPositions[2]);
        obj.setVec3("pointLights[2].ambient", 0.1f, 0.1f, 0.1f);
        obj.setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
        obj.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
        obj.setFloat("pointLights[2].constant", 1.0f);
        obj.setFloat("pointLights[2].linear", 0.09);
        obj.setFloat("pointLights[2].quadratic", 0.032);
        // point light 4
        obj.setVec3("pointLights[3].position", pointLightPositions[3]);
        obj.setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
        obj.setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
        obj.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
        obj.setFloat("pointLights[3].constant", 1.0f);
        obj.setFloat("pointLights[3].linear", 0.09);
        obj.setFloat("pointLights[3].quadratic", 0.032);
        // spotLight
        obj.setVec3("spotLight.position", c.Position);
        obj.setVec3("spotLight.direction", c.Front);
        obj.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
        obj.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
        obj.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
        obj.setFloat("spotLight.constant", 1.0f);
        obj.setFloat("spotLight.linear", 0.09);
        obj.setFloat("spotLight.quadratic", 0.032);
        obj.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
        obj.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

        obj.setMat4("projection", projection);
        obj.setMat4("view", view);
        model = glm::translate(model, glm::vec3(1.0f,2.0f,1.0f));
        obj.setMat4("model", model);
        glBindVertexArray(VAO[1]);
        glDrawElements(GL_TRIANGLES,o1.S.size(),GL_UNSIGNED_INT,0);

        light.use();
        light.setMat4("projection",projection);
        light.setMat4("view",view);
        glBindVertexArray(VAO[2]);
        for(unsigned int i=0;i<4;i++){
            model = glm::mat4(1.0f);
            model = glm::translate(model,pointLightPositions[i]);
            model = glm::scale(model,glm::vec3(0.2f));
            light.setMat4("model",model);
            glDrawArrays(GL_TRIANGLES,0,36);
        }

        running();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(3, VAO);
    glDeleteBuffers(3, VBO);
    glDeleteBuffers(3, EBO);
    glDeleteProgram(s.ID);
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        c.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        c.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        c.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        c.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window,GLFW_KEY_UP)==GLFW_PRESS)
        c.ProcessMouseMovement(0,1);
    if (glfwGetKey(window,GLFW_KEY_DOWN)==GLFW_PRESS)
        c.ProcessMouseMovement(0,-1);
    if (glfwGetKey(window,GLFW_KEY_LEFT)==GLFW_PRESS)
        c.ProcessMouseMovement(-1,0);
    if (glfwGetKey(window,GLFW_KEY_RIGHT)==GLFW_PRESS)
        c.ProcessMouseMovement(1,0);
    if (glfwGetKey(window,GLFW_KEY_A)==GLFW_PRESS)
        c.ProcessRoll(1);
    if (glfwGetKey(window,GLFW_KEY_D)==GLFW_PRESS)
        c.ProcessRoll(-1);
    if (glfwGetKey(window,GLFW_KEY_EQUAL)==GLFW_PRESS)
        if(speed<5)
        speed+=0.0005;
    if (glfwGetKey(window,GLFW_KEY_MINUS)==GLFW_PRESS)
        if(speed>0.0005)
        speed-=0.0005;
    if (glfwGetKey(window,GLFW_KEY_U)==GLFW_PRESS)
        if(ambient>0.0005)
            ambient-=0.0005;
    if (glfwGetKey(window,GLFW_KEY_J)==GLFW_PRESS)
        if(ambient<1)
            ambient+=0.0005;
    if (glfwGetKey(window,GLFW_KEY_I)==GLFW_PRESS)
        if(diffuse>0.0005)
            diffuse-=0.0005;
    if (glfwGetKey(window,GLFW_KEY_K)==GLFW_PRESS)
        if(diffuse<1)
            diffuse+=0.0005;


}

void running(){
    c.ProcessKeyboard(FORWARD, speed*deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (action == GLFW_PRESS) switch(button)
        {
            case GLFW_MOUSE_BUTTON_LEFT:
            {
                Click= true;
                firstMouse= true;
            }
                break;
            case GLFW_MOUSE_BUTTON_MIDDLE:
                break;
            case GLFW_MOUSE_BUTTON_RIGHT:
                break;
            default:
                return;
        }else{
        Click = false;
    }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    if(!Click){
        return;
    }
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    c.ProcessMouseMovement(xoffset,yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    c.ProcessMouseScroll(yoffset);
}

unsigned int loadTexture(const char *path){
    unsigned int textureID;
    glGenTextures(1,&textureID);
    int width,height,nrComponents;
    unsigned char* data = stbi_load(path,&width,&height,&nrComponents,0);
    if(data){
        GLenum format;
        if(nrComponents==1){
            format=GL_RED;
        }else if(nrComponents==3){
            format = GL_RGB;
        }else if(nrComponents==4){
            format = GL_RGBA;
        }
        glBindTexture(GL_TEXTURE_2D,textureID);
        glTexImage2D(GL_TEXTURE_2D,0,format,width,height,0,format,GL_UNSIGNED_BYTE,data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }else{
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }
    return textureID;
}