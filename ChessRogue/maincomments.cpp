//this is just for unused code that is not used, but may be useful rather than deleted
/*


void renderModel(const aiMesh* mesh, float xOffset) {
    glBegin(GL_TRIANGLES);
    for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
        const aiFace& face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; ++j) {
            unsigned int index = face.mIndices[j];
            glVertex3f(mesh->mVertices[index].x + xOffset, mesh->mVertices[index].y, mesh->mVertices[index].z);
        }
    }
    glEnd();
}




 for (unsigned int i = 0; i < scene->mNumMeshes; ++i) {
                const aiMesh* mesh = scene->mMeshes[i];
                glLoadIdentity();
                glMatrixMode(GL_MODELVIEW);
                glLoadMatrixf(glm::value_ptr(view));
                glMatrixMode(GL_PROJECTION);
                glLoadMatrixf(glm::value_ptr(projection));
                renderModel(mesh, modelXPosition1);
            }

            for (unsigned int i = 0; i < scene2->mNumMeshes; ++i) {
                const aiMesh* mesh = scene2->mMeshes[i];
                glLoadIdentity();
                glMatrixMode(GL_MODELVIEW);
                glLoadMatrixf(glm::value_ptr(view));
                glMatrixMode(GL_PROJECTION);
                glLoadMatrixf(glm::value_ptr(projection));
                renderModel(mesh, modelXPosition2);
            }










              // Initializes the glew library
   /* GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW: " << glewGetErrorString(err) << std::endl;
        return -1;
    }
    
    
    
    //void mouse_callback(int x, int y) {
//    if (firstMouse) {
//        lastX = x;
//        lastY = y;
//        firstMouse = false;
//    }
//
//    float xoffset = x - lastX;
//    float yoffset = lastY - y; // reversed since y-coordinates range from bottom to top
//    lastX = x;
//    lastY = y;
//
//    float sensitivity = 0.5f;
//    xoffset *= sensitivity;
//    yoffset *= sensitivity;
//
//    yaw += xoffset;
//    pitch += yoffset;
//
//    // Make sure that when pitch is out of bounds, screen doesn't get flipped
//    if (pitch > 89.0f)
//        pitch = 89.0f;
//    if (pitch < -89.0f)
//        pitch = -89.0f;
//
//    glm::vec3 front;
//    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
//    front.y = sin(glm::radians(pitch));
//    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
//    cameraFront = glm::normalize(front);
//    glutPostRedisplay();
//}
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    */





