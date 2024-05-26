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
#include <ctime>
#include <cmath>
#include <cstdlib>

//custom header files
#include "keyboard.h"
#include "render.h"
#include "timer.h"
#include "Chesspieces.h"


//gamestart bool
bool gamestart = false;

//camera view vars
glm::mat4 view;
glm::mat4 projection;


//load scene
const extern aiScene* scene;

 //Camera parameters for white team
glm::vec3 cameraPos = glm::vec3(8.0f, 20.0f, 20.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, -0.5f, -0.7f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

//camera parameters for black team
//glm::vec3 cameraPos = glm::vec3(8.0f, 20.0f, -25.0f);
//glm::vec3 cameraFront = glm::vec3(0.0f, -0.5f, 0.7f);
//glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

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


float* g;


//Mouse controlling function, I believe it will be removed due to the camera being fixed in the future

//void mouse_callback(int x, int y) {
//    if (firstMouse) {
//        lastX = x;
//        lastY = y;
//        firstMouse = false;
//    }
//
//    float xoffset = x - lastX;
//    float yoffset = lastY - y; // reversed since y-coordinates range from bottom to top
//    lastX = x;
//    lastY = y;
//
//    float sensitivity = 0.5f;
//    xoffset *= sensitivity;
//    yoffset *= sensitivity;
//
//    yaw += xoffset;
//    pitch += yoffset;
//
//    // Make sure that when pitch is out of bounds, screen doesn't get flipped
//    if (pitch > 89.0f)
//        pitch = 89.0f;
//    if (pitch < -89.0f)
//        pitch = -89.0f;
//
//    glm::vec3 front;
//    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
//    front.y = sin(glm::radians(pitch));
//    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
//    cameraFront = glm::normalize(front);
//    glutPostRedisplay();
//}

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
    const char* str = "Welcome to the ChessRogue Game\nPress N to start a new game and G to move one of the pawns ;)";
    int textWidth = glutBitmapLength(GLUT_BITMAP_HELVETICA_12, (const unsigned char*)str);
    int x = (windowWidth - textWidth) / 2; 
    int y = windowHeight / 2; 

    // Render the text
    renderText(x, y, GLUT_BITMAP_HELVETICA_12, str);
}

//intializing timers;
void intializeTimers(int num) {
    blackTimer.setDuration(std::chrono::minutes(num));
    whiteTimer.setDuration(std::chrono::minutes(num));
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
 /*   std::cout << "whiteTimer: " << std::chrono::duration_cast<std::chrono::seconds>(whiteTimer.remaining()).count() << std::endl;
    std::cout << "blackTimer: " << std::chrono::duration_cast<std::chrono::seconds>(blackTimer.remaining()).count() << std::endl;*/
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


void background() {

}




void board() {
    float size = 2.0f;
    bool color = false;
    int xy = 4;
    int zy = -2;

    for (int x = 0; x < 8; x++) {
        for (int z = -6; z < 2; z++) {
            if (color)
                glColor3f(0.8f, 0.8f, 0.8f); // White
            else
                glColor3f(0.2f, 0.2f, 0.2f); // Black

            glBegin(GL_QUADS);
            // Top
            glVertex3f(x * size, 0, z * size);
            glVertex3f((x + 1) * size, 0, z * size);
            glVertex3f((x + 1) * size, 0, (z + 1) * size);
            glVertex3f(x * size, 0, (z + 1) * size);
            glEnd();

            // Color swap to the front
            color = !color;
        }
        // Color swap to the side
        color = !color;
    }

    glColor3f(0.62, 0.35, 0.24);
    glBegin(GL_QUADS);
    // Top View Frames
    // Left frame
    glVertex3f((-6 + xy) * 2, -1, (-6 + zy) * 2);
    glVertex3f((-4 + xy) * 2, -1, (-6 + zy) * 2);
    glVertex3f((-4 + xy) * 2, -1, (6 + zy) * 2);
    glVertex3f((-6 + xy) * 2, -1, (6 + zy) * 2);

    // Back frame
    glVertex3f((-4 + xy) * 2, -1, (6 + zy) * 2);
    glVertex3f((-4 + xy) * 2, -1, (4 + zy) * 2);
    glVertex3f((6 + xy) * 2, -1, (4 + zy) * 2);
    glVertex3f((6 + xy) * 2, -1, (6 + zy) * 2);

    // Right frame
    glVertex3f((4 + xy) * 2, -1, (-6 + zy) * 2);
    glVertex3f((4 + xy) * 2, -1, (6 + zy) * 2);
    glVertex3f((6 + xy) * 2, -1, (6 + zy) * 2);
    glVertex3f((6 + xy) * 2, -1, (-6 + zy) * 2);

    // Forward frame
    glVertex3f((-4 + xy) * 2, -1, (-4 + zy) * 2);
    glVertex3f((-4 + xy) * 2, -1, (-6 + zy) * 2);
    glVertex3f((6 + xy) * 2, -1, (-6 + zy) * 2);
    glVertex3f((6 + xy) * 2, -1, (-4 + zy) * 2);

    // Side View Frames
    // Left frame
    glVertex3f((-6 + xy) * 2, -1, (-6 + zy) * 2);
    glVertex3f((-6 + xy) * 2, -2, (-6 + zy) * 2);
    glVertex3f((-6 + xy) * 2, -2, (6 + zy) * 2);
    glVertex3f((-6 + xy) * 2, -1, (6 + zy) * 2);

    // Back frame
    glVertex3f((-6 + xy) * 2, -1, (6 + zy) * 2);
    glVertex3f((-6 + xy) * 2, -2, (6 + zy) * 2);
    glVertex3f((6 + xy) * 2, -2, (6 + zy) * 2);
    glVertex3f((6 + xy) * 2, -1, (6 + zy) * 2);

    // Right frame
    glVertex3f((6 + xy) * 2, -1, (-6 + zy) * 2);
    glVertex3f((6 + xy) * 2, -2, (-6 + zy) * 2);
    glVertex3f((6 + xy) * 2, -2, (6 + zy) * 2);
    glVertex3f((6 + xy) * 2, -1, (6 + zy) * 2);

    // Forward frame
    glVertex3f((-4 + xy) * 2, -1, (-6 + zy) * 2);
    glVertex3f((-4 + xy) * 2, -2, (-6 + zy) * 2);
    glVertex3f((6 + xy) * 2, -2, (-6 + zy) * 2);
    glVertex3f((6 + xy) * 2, -1, (-6 + zy) * 2);

    // Bottom view
    glVertex3f((-6 + xy) * 2, -2, (-6 + zy) * 2);
    glVertex3f((6 + xy) * 2, -2, (-6 + zy) * 2);
    glVertex3f((6 + xy) * 2, -2, (6 + zy) * 2);
    glVertex3f((-6 + xy) * 2, -2, (6 + zy) * 2);

    glEnd();
}




//constructor of pawn takes in parameters of x and z positions
// array that makes 8 of them

Pawn whitepawn[8] = { Pawn(1.0f, 1.0f,0), Pawn(3.0f, 1.0f,0), Pawn(5.0f, 1.0f,0), Pawn(7.0f, 1.0f,0), Pawn(9.0f, 1.0f,0), Pawn(11.0f, 1.0f,0), Pawn(13.0f, 1.0f,0), Pawn(15.0f, 1.0f,0) };
Queen whitequeen(7.0f, 3.0f, 0);
Rook whiterook[2] = { Rook(1.0f, 3.0f,0), Rook(15.0f, 3.0f,0) };
Knight whiteknight[2] = { Knight(3.0f, 3.0f,0), Knight(13.0f, 3.0f,0) };
King whiteking(9.0f, 3.0f, 0);
Bishop whitebishop[2] = { Bishop(5.0f, 3.0f,0), Bishop(11.0f, 3.0f,0) };




Rook blackrook[2] = { Rook(1.0f, -11.0f,1), Rook(15.0f, -11.0f,1) };
Knight blackknight[2] = { Knight(3.0f, -11.0f,1), Knight(13.0f, -11.0f,1) };
King blackking(9.0f, -11.0f,1);
Pawn blackpawn[8] = { Pawn(1.0f, -9.0f,1), Pawn(3.0f, -9.0f,1), Pawn(5.0f, -9.0f,1), Pawn(7.0f, -9.0f,1), Pawn(9.0f, -9.0f,1), Pawn(11.0f, -9.0f,1), Pawn(13.0f, -9.0f,1), Pawn(15.0f, -9.0f,1) };
Queen blackqueen(7.0f, -11.0f, 1);
Bishop blackbishop[2] = { Bishop(5.0f, -11.0f,1), Bishop(11.0f, -11.0f,1) };

//Display function

void display() {
    // Set the background color and clear buffers
    glClearColor(0.2f, 0.6f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set the camera view
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);
    projection = glm::perspective(glm::radians(fov), static_cast<float>(width) / height, 0.1f, 100.0f);

    // Render the chessboard
    //board();

    // If the game has started, render the game elements
    if (gamestart) {
        // Render the timer
        timerText();
        std:: cout <<cameraFront.x << " " << cameraFront.y << " " << cameraFront.z << std::endl;
        // Callback for the timer
        glutTimerFunc(1000 / 60, timerCallback, 0);
        currentTimer->countDown();

       

        // Render the chess pieces
        for (int i = 0; i < 8; i++) {
            whitepawn[i].Load(view, projection);
            blackpawn[i].Load(view, projection);
        }
        for (int i = 0; i < 2; i++) {
			whiterook[i].Load(view, projection);
			blackrook[i].Load(view, projection);
            whiteknight[i].Load(view, projection);
            blackknight[i].Load(view, projection);
            whitebishop[i].Load(view, projection);
            blackbishop[i].Load(view, projection);
		}
        whitequeen.Load(view, projection);
        blackqueen.Load(view, projection);
        whiteking.Load(view, projection);
        blackking.Load(view, projection);
       
    }
    else {
        // Display welcome text
        welcometext();
    }
    board();
    // Swap buffers
    glutSwapBuffers();
}


void reshape(int w, int h) { //Not sure what this does but it has to do with camera settings
    if (h == 0) h = 1; // Prevent divide by zero
    float aspect = (float)w / (float)h;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, aspect, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}






int main(int argc, char** argv) {
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Roguelike Chess");
    
    
    
    intializeTimers(timeSeconds);

    if(gamestart)
        //renders the 8 pawns
        for (int i = 0; i < 8; i++) {
            whitepawn[i].Load(view, projection);
            std::cout << "loaded" << std::endl;
        }

    //sets the g float pointer to point to one of the object's z position so that it gets changed in the keyboard.cpp;
    g=&whitepawn[1].modelZPosition;
    
   

    //display and control related functions

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    //glutPassiveMotionFunc(mouse_callback);

    //process input is a function in keyboard.cpp that takes in the keyboard input and processes it accordingly
    glutKeyboardFunc(processInput);
        

    glClearDepth(1.0f);
    // makes the 3d model have a depth feel to it
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glutMainLoop();
    return 0;
}
