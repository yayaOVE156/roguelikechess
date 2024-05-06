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



//gamestart bool
bool gamestart = false;
// Define the global scene variable
const aiScene* scene = nullptr;

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

void display() {

    glClearColor(0.2f, 0.6f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set up view and projection matrices
    glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);
    glm::mat4 projection = glm::perspective(glm::radians(fov), static_cast<float>(width) / height, 0.1f, 100.0f);

    // Render the scene
    if (gamestart) {
        renderer pawntest(scene, view, projection, 0.0f);
        pawntest.Render();
    }
    else {
        welcometext();
    }

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
}

int main(int argc, char** argv) {
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Roguelike Chess");

    Assimp::Importer importer;
    scene = importer.ReadFile("../OpenGL Models/Pawn.obj", aiProcess_Triangulate | aiProcess_FlipUVs);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "Error loading model: " << importer.GetErrorString() << std::endl;
        return -1;
    }
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutPassiveMotionFunc(mouse_callback);
    glutKeyboardFunc(processInput);


    // Initialize GLEW
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW: " << glewGetErrorString(err) << std::endl;
        return -1;
    }

    // Load the model using Assimp
    

    glEnable(GL_DEPTH_TEST);

    glutMainLoop();
    return 0;
}
