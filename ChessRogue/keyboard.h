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

void processInput(unsigned char key, int x, int y);
