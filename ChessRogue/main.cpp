#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <iomanip>
#include <iostream>

//custom header files
#include "keyboard.h"
#include "render.h"
#include "timer.h"

//gamestart bool
bool gamestart = false;

// Model pointers
const aiScene* scene = nullptr;

// Camera parameters
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 10.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

//timers
int timeMinutes = 10;
int timeSeconds = 10;

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



// Convert duration to minutes and seconds (string)
    

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

// calculate width of text
int getTextWidth(void* font, const std::string& text) {
    int width = 0;
    for (const char& c : text) {
        width += glutBitmapWidth(font, c);
    }
    return width;
}


// Render the bitmap string (message)
void renderText(float x, float y, void* font, const char* string) {
    const char* c;
    //position the text
    glRasterPos2f(x, y);
    for (c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
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

    // Render the text
    renderText(x, y, GLUT_BITMAP_HELVETICA_12, str);
}

//intializing timers;
void intializeTimers(int num) {
    blackTimer.setDuration(std::chrono::seconds(num));
    whiteTimer.setDuration(std::chrono::seconds(num));
}

void timerCallback(int value) {
    if (currentTimer != nullptr && currentTimer->isAlive()) {
        glutPostRedisplay();
        glutTimerFunc(1000 / 60, timerCallback, 0);
    }   
}

void checkTimeOut() {
    if (currentTimer != nullptr && !currentTimer->isAlive()) {
        "this team has lost";
    }
    std::cout << "whiteTimer: " << std::chrono::duration_cast<std::chrono::seconds>(whiteTimer.remaining()).count() << std::endl;
    std::cout << "blackTimer: " << std::chrono::duration_cast<std::chrono::seconds>(blackTimer.remaining()).count() << std::endl;
}


//Timer Text
void timerText() {
    using namespace std;

    glClear(GL_COLOR_BUFFER_BIT);

    // Set up projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 1000, 0, 1000);

    // Set up modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if(teamColor == black)
        glColor3f(0.0f, 0.0f, 0.0f);
    else
        glColor3f(1.0f, 1.0f, 1.0f);


    // Calculate text position
    const std::string timerString = currentTimer->remainingTimeString();
    const char* timeChar = timerString.c_str();
    int textWidth = getTextWidth(GLUT_BITMAP_HELVETICA_18, timerString);
    int x = (windowWidth - textWidth) / 2;
    int y = 950;

    //Render Text
    renderText(x, y, GLUT_BITMAP_HELVETICA_18, timeChar);
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



//Display function

void display() {
    //sets the color for the background
    glClearColor(0.2f, 0.6f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // sets the camera view
    glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);
    glm::mat4 projection = glm::perspective(glm::radians(fov), static_cast<float>(width) / height, 0.1f, 100.0f);

    // checks if welcome text is displayed or not, if it is not displayed then the player has pressed N to start the game
    //When the game starts it begins to render the models
    if (gamestart) {

        //Makes an instance of renderer object from renderer class and sends the scene(which has the model loaded) the window and projection matrix
        renderer pawntest(scene, view, projection, 0.0f);
        //renders the model
        pawntest.Render();
        //render the timer
        timerText();
        //callback for the timer
            glutTimerFunc(1000 / 60, timerCallback, 0);
    }
    else {
        welcometext();
    }
    checkTimeOut();
    glutSwapBuffers();
}

void reshape(int w, int h) { //Not sure what this does but it has to do with camera settings
    glViewport(0, 0, w, h);
}



void importer(std::string path) {
    Assimp::Importer importer;
	scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cerr << "Error loading model: " << importer.GetErrorString() << std::endl;
	}
}



int main(int argc, char** argv) {
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Roguelike Chess");


    //intialize timers
    intializeTimers(timeSeconds);


    //makes an assimp instance importer object which loads in the model
    Assimp::Importer importer;
    scene = importer.ReadFile("../OpenGL Models/Pawn.obj", aiProcess_Triangulate | aiProcess_FlipUVs);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "Error loading model: " << importer.GetErrorString() << std::endl;
        return -1;
    }

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
