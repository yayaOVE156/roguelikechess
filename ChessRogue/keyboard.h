#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string.h>

void processInput(GLFWwindow* window, glm::vec3& cameraPos, glm::vec3& cameraFront, float& cameraSpeed, int& selectedModelIndex, float& modelXPosition1, float& modelXPosition2, bool& gamestart);
