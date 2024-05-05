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
#include "keyboard.h"

void processInput(GLFWwindow* window, glm::vec3& cameraPos, glm::vec3& cameraFront, float& cameraSpeed, int& selectedModelIndex, float& modelXPosition1, float& modelXPosition2, bool& gamestart) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);


    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
        gamestart = true;
        glColor3f(1.0f, 1.0f, 1.0f);
    }
    // Camera controls
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        cameraPos += cameraSpeed * cameraFront;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        cameraPos -= cameraSpeed * cameraFront;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        cameraPos -= glm::normalize(glm::cross(cameraFront, glm::vec3(0.0f, 1.0f, 0.0f))) * cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        cameraPos += glm::normalize(glm::cross(cameraFront, glm::vec3(0.0f, 1.0f, 0.0f))) * cameraSpeed;
    }
    // model select
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        // model toggle
        selectedModelIndex = (selectedModelIndex == 0) ? 1 : 0;
    }

    // movement
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS && selectedModelIndex != -1) {
        // Move the selected model in the x-direction
        if (selectedModelIndex == 0) {
            modelXPosition1 += 0.1f; // Adjust the movement amount as needed
        }
        else {
            modelXPosition2 += 0.1f; // Adjust the movement amount as needed
        }
    }
}