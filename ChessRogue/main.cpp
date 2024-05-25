#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "keyboard.h"
#include "render.h"
#include <string>
#include "Chesspieces.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <chrono>


#include "ChessGame.h"


//gamestart bool
bool gamestart = false;



// Model pointers white
const aiScene* scene;



// Camera parameters
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 10.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

// Camera movement speed
float cameraSpeed = 0.05f;

// Mouse input
bool firstMouse = true;
float lastX = 400, lastY = 300;
float yaw = -90.0f, pitch = 0.0f;
float fov = 45.0f;


// window stuff
int windowWidth = 1000;
int windowHeight = 1000;


float* g;


//Mouse controlling function, I believe it will be removed due to the camera being fixed in the future

void mouse_callback(int x, int y) {
    if (firstMouse) {
        lastX = x;
        lastY = y;
        firstMouse = false;
    }

    float xoffset = x - lastX;
    float yoffset = lastY - y; // reversed since y-coordinates range from bottom to top
    lastX = x;
    lastY = y;

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
    glutPostRedisplay();
}

//welcome text, all it does is just display a welcome message and instruction to start the game
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
    int x = (windowWidth - textWidth) / 2; 
    int y = windowHeight / 2; 

    // Position the text
    glRasterPos2i(x, y);

    // Render the text
    for (int i = 0; str[i] != '\0'; ++i) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, str[i]);
    };
}




//void renderModel(const aiMesh* mesh) {
//    glBegin(GL_TRIANGLES);
//    for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
//        const aiFace& face = mesh->mFaces[i];
//        for (unsigned int j = 0; j < face.mNumIndices; ++j) {
//            unsigned int index = face.mIndices[j];
//            glVertex3fv(reinterpret_cast<const GLfloat*>(&mesh->mVertices[index]));
//        }
//    }
//    glEnd();
//}


Pawn whitepawn[8] = { Pawn(0.0f, 0.0f), Pawn(4.0f, 0.0f), Pawn(8.0f, 0.0f), Pawn(12.0f, 0.0f), Pawn(16.0f, 0.0f), Pawn(20.0f, 0.0f), Pawn(24.0f, 0.0f), Pawn(28.0f, 0.0f) };
//Display function

std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();
const int gameTime = 600; // 10 minutes in seconds
int timeRemaining = gameTime;

// Function to update the timer
void updateTimer() {
    std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
    std::chrono::duration<float> elapsedTime = currentTime - startTime;
    timeRemaining = gameTime - static_cast<int>(elapsedTime.count());
    if (timeRemaining < 0) {
        timeRemaining = 0; // Ensure timeRemaining doesn't go negative
    }
}

// Function to render the timer on the screen


// Function to render the timer in 2D
void renderTimer() {
    int minutes = timeRemaining / 60;
    int seconds = timeRemaining % 60;

    // Set up 2D projection
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT));
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Render the timer on the screen
    int xPos = 10; // Adjust X position
    int yPos = glutGet(GLUT_WINDOW_HEIGHT) - 20; // Adjust Y position
    glColor3f(1.0f, 1.0f, 1.0f);
    std::string timerString = "Time Remaining: " + std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + std::to_string(seconds);
    glRasterPos2i(xPos, yPos);
    for (const char& c : timerString) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }

    // Restore original projection
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}



void display() {
    glClearColor(1.0f, 0.5f, 0.0f,1.0f);
    // Clear the color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set up the gradient colors
    glm::vec3 sunsetColor1 = glm::vec3(1.0f, 0.5f, 0.0f); // Orange color
    glm::vec3 sunsetColor2 = glm::vec3(1.0f, 0.0f, 1.0f); // Purple color

    // Define the gradient direction (from bottom to top)
    glm::vec3 gradientDirection = glm::vec3(0.0f, 1.0f, 0.0f);

    // Get the window height
    int height = glutGet(GLUT_WINDOW_HEIGHT);
    int width = glutGet(GLUT_WINDOW_WIDTH);

  
    

    glBegin(GL_QUADS);
    // Lower part of the sky (sunset)
    glColor3fv(glm::value_ptr(sunsetColor1)); // Bottom color
    glVertex3f(-width / 2.0f, -height / 2.0f, -50.0f);
    glVertex3f(width / 2.0f, -height / 2.0f, -50.0f);
    glColor3fv(glm::value_ptr(sunsetColor2)); // Top color
    glVertex3f(width/ 2.0f, height / 2.0f, -50.0f);
    glVertex3f(-width / 2.0f, height / 2.0f, -50.0f);
    glEnd();
  // Draw the sun at the center of the window
    float sunSize = 2.0f; // Size of the sun
    int numSegments = 50; // Number of segments to approximate the sun shape

    glColor3f(1.0f, 0.4f, 0.0f); // Yellow color for the sun
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, 0.0f, -1.0f); // Center of the sun
    for (int i = 0; i <= numSegments; i++) {
        float angle = static_cast<float>(i) / static_cast<float>(numSegments) * 2.0f * M_PI;
        float x = sunSize * cos(angle);
        float y = sunSize * sin(angle);
        glVertex3f(x, y, -1.0f);
    }
    glEnd();

    

    // Set up the view and projection matrices
    glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    
    glm::mat4 projection = glm::perspective(glm::radians(fov), static_cast<float>(width) / height, 0.1f, 100.0f);

    

    // checks if welcome text is displayed or not, if it is not displayed then the player has pressed N to start the game
    //When the game starts it begins to render the models
    if (gamestart) {
        updateTimer(); // Update the timer
        renderTimer(); // Render the timer
      
       //renders the 8 pawns
        for (int i = 0; i < 8; i++) {
			whitepawn[i].Render(view, projection);
		}
        
        
        //modelzposition never changes

       
       
            

        		
		
    }
    else {
        welcometext();
    }

    glutSwapBuffers();
}

void reshape(int w, int h) { //Not sure what this does but it has to do with camera settings
    glViewport(0, 0, w, h);
}






int main(int argc, char** argv) {


    //StartChessGame();
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Roguelike Chess");

    g=&whitepawn[1].modelZPosition;
    
    //makes an assimp instance importer object which loads in the model
    Assimp::Importer importer;  
    scene = importer.ReadFile("../OpenGL Models/pawn.obj", aiProcess_Triangulate | aiProcess_FlipUVs);

    //display and control related functions

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutPassiveMotionFunc(mouse_callback);

    //process input is a function in keyboard.cpp that takes in the keyboard input and processes it accordingly
    glutKeyboardFunc(processInput);

   
  

  
    
    // makes the 3d model have a depth feel to it
    glEnable(GL_DEPTH_TEST);

    glutMainLoop();
    return 0;
}
