#include <GL/glew.h>
#include "keyboard.h"

//var of type teams (equal white since they always start)
teams teamColor;

//vars for Timers
 Timer blackTimer;
 Timer whiteTimer;
 extern Timer* currentTimer = nullptr;

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
        teamColor = white;
        currentTimer = &whiteTimer;
        currentTimer->start();
        break;
        
    case 't':
        currentTimer->stop();
        if (teamColor == white) {
            teamColor = black;
            currentTimer = &blackTimer;
            printf("current team is black");
        }
        else {
            teamColor = white;
            currentTimer = &whiteTimer;
            printf("current team is white");
        }
        currentTimer->start(currentTimer->remainingTime());
        break;
    case 'r':
        std::cout << "remaining time: " << std::chrono::duration_cast<std::chrono::seconds>(currentTimer->remainingTime()).count() << std::endl;
    
		break;

    case 'g':
        //increment the modelz position of the pawn
        (*g)++;
        break;
    }

    glutPostRedisplay();
}