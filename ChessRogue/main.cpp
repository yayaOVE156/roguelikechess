#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <string>
#include "keyboard.h"
#include "render.h"



//gamestart bool
bool gamestart = false;
// camera
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 7.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 4.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float cameraSpeed = 0.05f;

// Mouse input
bool firstMouse = true;
float lastX = 400, lastY = 300;
float yaw = -90.0f, pitch = 0.0f;
float fov = 45.0f;

// model to select
int selectedModelIndex = 0;

// what controls model movement
float modelXPosition1 = 0.0f;
float modelXPosition2 = 4.0f;




void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates range from bottom to top
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.05f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    if (fov >= 1.0f && fov <= 45.0f)
        fov -= yoffset;
    if (fov <= 1.0f)
        fov = 1.0f;
    if (fov >= 45.0f)
        fov = 45.0f;
}



void welcometext() {
    using namespace std;

    glClear(GL_COLOR_BUFFER_BIT);

    // Set up projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 1000, 0, 1000);

    // Set up modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    
    glColor3f(0.0f, 0.0f, 0.0f); 

    // Calculate text position
    const char* str = "Welcome to the ChessRogue Game\nPress N to start a new game";
    int textWidth = glutBitmapLength(GLUT_BITMAP_HELVETICA_12, (const unsigned char*)str);
    int x = (1000 - textWidth) / 2; // Center horizontally
    int y = 1000 / 2; // Center vertically

    // Position the text
    glRasterPos2i(x, y);

    // Render the text
    for (int i = 0; str[i] != '\0'; ++i) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, str[i]);
    };
}


int main(int argc, char** argv) {


    glutInit(&argc, argv);

    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // GLFW window creation
    GLFWwindow* window = glfwCreateWindow(1000, 1000, "Rougelike Chess", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // Initialize GLEW
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW: " << glewGetErrorString(err) << std::endl;
        return -1;
    }
    glClear(GL_COLOR_BUFFER_BIT);
 
    glfwSwapBuffers(window);
    // imports the models 1 and 2 respectively
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile("../OpenGL Models/Bishop.obj", aiProcess_Triangulate | aiProcess_FlipUVs);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "Error loading model: " << importer.GetErrorString() << std::endl;
        return -1;
    }
    Assimp::Importer importer2;
    const aiScene* scene2 = importer2.ReadFile("../OpenGL Models/Pawn.obj", aiProcess_Triangulate | aiProcess_FlipUVs);
    if (!scene2 || scene2->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "Error loading model: " << importer.GetErrorString() << std::endl;
        return -1;
    }

    // OpenGL setup
    glEnable(GL_DEPTH_TEST);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Process input

        processInput(window, cameraPos, cameraFront, cameraSpeed, selectedModelIndex, modelXPosition1, modelXPosition2,gamestart);

        // Clear the color and depth buffers aka background color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Set up view and projection matrices
        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glm::mat4 projection = glm::perspective(glm::radians(fov), static_cast<float>(width) / height, 0.1f, 100.0f);


        
        if (gamestart) {

            renderer bishoptest(scene, view, projection, modelXPosition1);
            renderer pawntest(scene2, view, projection, modelXPosition2);
            bishoptest.Render();
            pawntest.Render();

            // prepares the models for rendering
           

        }
        else {
            welcometext();
        }

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();
    return 0;
}