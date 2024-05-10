#include <GL/glew.h>
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
        if (currentTimer == &whiteTimer) {
            whiteTimer.start();
            currentTimer = &whiteTimer;
        }
    case 't':
        if (currentTimer == &whiteTimer) {
            whiteTimer.stop();
            blackTimer.start();
            currentTimer = &blackTimer;
        }
        else {
            blackTimer.stop();
            whiteTimer.start();
            currentTimer = &whiteTimer;
        }
        break;
        
    }

    glutPostRedisplay();
}