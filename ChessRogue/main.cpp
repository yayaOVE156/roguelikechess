#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/norm.hpp>
#include <string>
#include <iomanip>
#include <iostream>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <vector>

//custom header files
#include "keyboard.h"
#include "background.h"
#include "timer.h"
#include "Chesspieces.h"
#include "bimap.h"
#include "ChessGame.h"




#define M_PI 3.14159265358979323846

//gamestart bool
bool gamestart = false;

bool team = false;

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


Bimap <XZ , std::string> posmap;

void mapinit() {
    using namespace std;
    string letter = "A";
    int num = 1;
    for (int i = 1; i < 16; i += 2) {
        for (int j = 3; j > -12; j -= 2) {
            string pos= letter[0] + to_string(num);
            XZ cords(i, j);
            posmap.insert(cords, pos);
            if (letter == "H") {
				letter = "A";
				num++;
			}
            else {
				letter[0]++;
			}

           
        }
			
	}
    

}


float* g;


//Mouse controlling function, I believe it will be removed due to the camera being fixed in the future
 float squareX = 1.0f;
 float squareZ = 3.0f;
 float squareY = 0.5f;

void drawHollowSquare() {
   
    float outerSize = 1.0f;
    float innerSize = 0.75f;

    glPushMatrix(); // Save the current transformation matrix


    glColor3f(1.0, 0.0, 0.0); // Set the color to red
    glBegin(GL_LINES);

    // Draw outer square
    glVertex3f(-outerSize + squareX, squareY, outerSize + squareZ);
    glVertex3f(outerSize + squareX, squareY, outerSize + squareZ);

    glVertex3f(outerSize + squareX, squareY, outerSize + squareZ);
    glVertex3f(outerSize + squareX, squareY, -outerSize + squareZ);

    glVertex3f(outerSize + squareX, squareY, -outerSize + squareZ);
    glVertex3f(-outerSize + squareX, squareY, -outerSize + squareZ);

    glVertex3f(-outerSize + squareX, squareY, -outerSize + squareZ);
    glVertex3f(-outerSize + squareX, squareY, outerSize + squareZ);

    // Draw inner square
    glVertex3f(-innerSize + squareX, squareY, innerSize + squareZ);
    glVertex3f(innerSize + squareX, squareY, innerSize + squareZ);

    glVertex3f(innerSize + squareX, squareY, innerSize + squareZ);
    glVertex3f(innerSize + squareX, squareY, -innerSize + squareZ);

    glVertex3f(innerSize + squareX, squareY, -innerSize + squareZ);
    glVertex3f(-innerSize + squareX, squareY, -innerSize + squareZ);

    glVertex3f(-innerSize + squareX, squareY, -innerSize + squareZ);
    glVertex3f(-innerSize + squareX, squareY, innerSize + squareZ);

    // Connect outer and inner square
    glVertex3f(-outerSize + squareX, squareY, outerSize + squareZ);
    glVertex3f(-innerSize + squareX, squareY, innerSize + squareZ);

    glVertex3f(outerSize + squareX, squareY, outerSize + squareZ);
    glVertex3f(innerSize + squareX, squareY, innerSize + squareZ);

    glVertex3f(outerSize + squareX, squareY, -outerSize + squareZ);
    glVertex3f(innerSize + squareX, squareY, -innerSize + squareZ);

    glVertex3f(-outerSize + squareX, squareY, -outerSize + squareZ);
    glVertex3f(-innerSize + squareX, squareY, -innerSize + squareZ);


    glEnd();

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

void starttext() {
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
    const char* str = "ROGUELIKECHESS";
    int textWidth = glutBitmapLength(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)str);
    int x = (windowWidth - textWidth) / 2;
    int y = windowHeight - 100;

    // Render the text
    renderText(x, y, GLUT_BITMAP_HELVETICA_18, str);
}

void welcometext() {
    using namespace std;

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
    int y = windowHeight / 2 - 50; // Adjusted y position to ensure it does not overlap with starttext

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
        glColor3f(0.5f, 0.5f, 0.5f);
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



int wScore = 0;
int bScore = 0;



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


//white team
std::vector<Pawn> whitepawns = { Pawn(1.0f, 1.0f,0), Pawn(3.0f, 1.0f,0), Pawn(5.0f, 1.0f,0), Pawn(7.0f, 1.0f,0), Pawn(9.0f, 1.0f,0), Pawn(11.0f, 1.0f,0), Pawn(13.0f, 1.0f,0), Pawn(15.0f, 1.0f,0) };
std::vector<Knight> whiteknights = { Knight(3.0f, 3.0f,0), Knight(13.0f, 3.0f,0) };
std::vector<Rook> whiterooks = { Rook(1.0f, 3.0f,0), Rook(15.0f, 3.0f,0) };
std::vector<Bishop> whitebishops = { Bishop(5.0f, 3.0f,0), Bishop(11.0f, 3.0f,0) };
Queen whitequeen(7.0f, 3.0f, 0);
King whiteking(9.0f, 3.0f, 0);



//black team
std::vector<Pawn> blackpawns= { Pawn(1.0f, -9.0f,1), Pawn(3.0f, -9.0f,1), Pawn(5.0f, -9.0f,1), Pawn(7.0f, -9.0f,1), Pawn(9.0f, -9.0f,1), Pawn(11.0f, -9.0f,1), Pawn(13.0f, -9.0f,1), Pawn(15.0f, -9.0f,1) };
std::vector<Knight> blackknights= { Knight(3.0f, -11.0f,1), Knight(13.0f, -11.0f,1) };
std::vector<Rook> blackrooks= { Rook(1.0f, -11.0f,1), Rook(15.0f, -11.0f,1) };
std::vector<Bishop> blackbishops= { Bishop(5.0f, -11.0f,1), Bishop(11.0f, -11.0f,1) };
Queen blackqueen(7.0f, -11.0f, 1);
King blackking(9.0f, -11.0f,1);


void background1() {
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);
    glm::vec3 sunsetColor1 = glm::vec3(1.0f, 0.5f, 0.0f); // Orange color
    glm::vec3 sunsetColor2 = glm::vec3(1.0f, 0.0f, 1.0f); // Purple color
    glBegin(GL_QUADS);
    // Lower part of the sky (sunset)
    glColor3fv(glm::value_ptr(sunsetColor1)); // Bottom color
    glVertex3f(-width / 2.0f, -height / 2.0f, -50.0f);
    glVertex3f(width / 2.0f, -height / 2.0f, -50.0f);
    glColor3fv(glm::value_ptr(sunsetColor2)); // Top color
    glVertex3f(width / 2.0f, height / 2.0f, -50.0f);
    glVertex3f(-width / 2.0f, height / 2.0f, -50.0f);
    glEnd();
    // Draw the sun at the center of the window
    float sunSize = 2.0f; // Size of the sun
    int numSegments = 50; // Number of segments to approximate the sun shape

    glColor3f(1.0f, 0.4f, 0.0f); // Yellow color for the sun
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, 0.0f, -49.0f); // Center of the sun
    for (int i = 0; i <= numSegments; i++) {
        float angle = static_cast<float>(i) / static_cast<float>(numSegments) * 2.0f * M_PI;
        float x = sunSize * cos(angle);
        float y = sunSize * sin(angle);
        glVertex3f(x, y, -49.0f);
    }
    glEnd();

}


void bacgkround2() {
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);

    // Define colors for the sky gradient
    glm::vec3 nightColor1 = glm::vec3(0.0f, 0.0f, 0.1f); // Dark blue
    glm::vec3 nightColor2 = glm::vec3(0.0f, 0.0f, 0.3f); // Slightly lighter blue

    glBegin(GL_QUADS);
    // Lower part of the sky (night)
    glColor3fv(glm::value_ptr(nightColor1)); // Bottom color
    glVertex3f(-width / 2.0f, -height / 2.0f, 50.0f);
    glVertex3f(width / 2.0f, -height / 2.0f, 50.0f);
    glColor3fv(glm::value_ptr(nightColor2));// Top color
    glVertex3f(width / 2.0f, height / 2.0f, 50.0f);
    glVertex3f(-width / 2.0f, height / 2.0f, 50.0f);
    glEnd();

    // Draw stars
    glColor3f(1.0f, 1.0f, 1.0f); // White color for stars
    glPointSize(2.0f); // Set the size of the points to represent stars
    glBegin(GL_POINTS);
    // Randomly scatter stars across the sky
    if (team) {
        for (int i = 0; i < 1000; i++) {
            float x = static_cast<float>(rand() % width) - width / 2.0f;
            float y = static_cast<float>(rand() % height) - height / 2.0f;
            float z = static_cast<float>(rand() % 100) - 50.0f; // Vary depth to create depth effect
            glVertex3f(x, y, z);
        }
        glEnd();
    }
    // Draw the moon at the center of the window
    float moonSize = 2.0f; // Size of the moon
    int numSegments = 50; // Number of segments to approximate the moon shape

    glColor3f(1.0f, 1.0f, 1.0f); // White color for the moon
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, 0.0f, 49.0f); // Center of the moon
    for (int i = 0; i <= numSegments; i++) {
        float angle = static_cast<float>(i) / static_cast<float>(numSegments) * 2.0f * M_PI;
        float x = moonSize * cos(angle);
        float y = moonSize * sin(angle);
        glVertex3f(x, y, 49.0f);
    }
    glEnd();
}



void scoretext(int whiteScore, int blackScore) {
    using namespace std;

    // Set up projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);

    // Set up modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(0.0f, 0.0f, 0.0f);

    // Render White Score
    stringstream whiteStream;
    whiteStream << "White Score: " << whiteScore;
    string whiteStr = whiteStream.str();
    renderText(10, windowHeight - 20, GLUT_BITMAP_HELVETICA_18, whiteStr.c_str());

    // Render Black Score
    stringstream blackStream;
    blackStream << "Black Score: " << blackScore;
    string blackStr = blackStream.str();
    renderText(10, windowHeight - 40, GLUT_BITMAP_HELVETICA_18, blackStr.c_str());
}
//Display function

void display() {
    // Set the background color and clear buffers
    glClearColor(0.2f, 0.6f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);
    // Set the camera view
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    
    projection = glm::perspective(glm::radians(fov), static_cast<float>(width) / height, 0.1f, 100.0f);

    // Render the chessboard
    //board();

    // If the game has started, render the game elements
    if (gamestart) {
        // Render the timer
        timerText();
        scoretext(wScore, bScore);
        // Callback for the timer
        glutTimerFunc(1000 / 60, timerCallback, 0);
        currentTimer->countDown();

       
        
        // Render the chess pieces
        for (int i = 0; i < 8; i++) {
            whitepawns[i].Load(view, projection);
            blackpawns[i].Load(view, projection);
        }
        for (int i = 0; i < 2; i++) {
			whiterooks[i].Load(view, projection);
			blackrooks[i].Load(view, projection);
            whiteknights[i].Load(view, projection);
            blackknights[i].Load(view, projection);
            whitebishops[i].Load(view, projection);
            blackbishops[i].Load(view, projection);
		}
        whitequeen.Load(view, projection);
        blackqueen.Load(view, projection);
        whiteking.Load(view, projection);
        blackking.Load(view, projection);
       // 
    }
    else {

      
        while (true) {
            starttext();
			welcometext();
			break;
        }
    }
    board();
    drawHollowSquare();
    background1();
    bacgkround2();
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



std::string move;
int* arrx = new int[50];
int* arry = new int[50];
int* arrs = new int[50];


int main(int argc, char** argv) {
    whitepawns[4].del();

    for (int i = 0; i < 50; i++) {
        arrx[i] = rand();
    }
    for (int i = 0; i < 50; i++) {
        arry[i] = rand();
    }
    for (int i = 0; i < 50; i++) {
        arrs[i] = rand();
    }
    mapinit();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Roguelike Chess");
    
    
    
    intializeTimers(timeSeconds);

    //if(gamestart)
    //    //renders the 8 pawns
    //    for (int i = 0; i < 8; i++) {
    //        whitepawn[i].Load(view, projection);
    //        std::cout << "loaded" << std::endl;
    //    }

    //sets the g float pointer to point to one of the object's z position so that it gets changed in the keyboard.cpp;
    g=&whitepawns[1].position.z;
    
   

    //display and control related functions

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    //glutPassiveMotionFunc(mouse_callback);

    //process input is a function in keyboard.cpp that takes in the keyboard input and processes it accordingly
    glutKeyboardFunc(processInput);
    glutSpecialFunc(specialKeys);


    glClearDepth(1.0f);
    // makes the 3d model have a depth feel to it
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
   

    
    glutMainLoop();
    return 0;
}
