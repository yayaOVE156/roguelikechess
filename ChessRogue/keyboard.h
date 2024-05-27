#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string.h>
#include "timer.h"

 extern Timer blackTimer;
 extern Timer whiteTimer;
 extern Timer* currentTimer;
 enum teams {
	white,
	black
};
extern teams teamColor;
extern glm::vec3 cameraPos;
extern glm::vec3 cameraFront;
extern glm::vec3 cameraUp;
extern float cameraSpeed;
extern bool gamestart;
extern float* g;
extern float squareX;
extern float squareZ;
extern bool team;

void processInput(unsigned char key, int x, int y);

void specialKeys(int key, int x, int y);


#endif // KEYBOARD_H