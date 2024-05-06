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

void processInput(unsigned char key, int x, int y) {
    if (key == 27) // ESC key
        exit(0);

    // Camera controls
    switch (key) {
    case 'w':
        cameraPos += cameraSpeed * cameraFront;
        break;
    case 's':
        cameraPos -= cameraSpeed * cameraFront;
        break;
    case 'a':
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        break;
    case 'd':
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        break;
    case'n':
		gamestart = true;
		break;
    }

    glutPostRedisplay();
}