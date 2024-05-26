#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "keyboard.h"

//var of type teams (equal white since they always start)
teams teamColor;

//vars for Timers
 Timer blackTimer;
 Timer whiteTimer;
 extern Timer* currentTimer = nullptr;

 extern glm::vec3 cameraPos;
 extern glm::vec3 cameraFront;
 extern glm::vec3 cameraUp;

void processInput(unsigned char key, int x, int y) {
    if (key == 27) // ESC key
        exit(0);

    // Camera controls
    switch (key) {
    case 'w':
         cameraPos = glm::vec3(8.0f, 20.0f, 20.0f);
         cameraFront = glm::vec3(0.0f, -0.5f, -0.7f);
         cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
        break;
    case 's':
         cameraPos = glm::vec3(8.0f, 20.0f, -28.0f);
         cameraFront = glm::vec3(0.0f, -0.5f, 0.7f);
         cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
        break;
    case 'a':
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        break;
    case 'd':
        cameraPos +=glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
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
        (*g) -= 2;
        std::cout << *g << std::endl;
        break;
    }

    glutPostRedisplay();
 }