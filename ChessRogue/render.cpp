#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <string>
#include "render.h"



renderer::renderer(const aiScene* scene, const glm::mat4& view, const glm::mat4& projection, float modelXPosition)
    : scene(scene), view(view), projection(projection), modelXPosition(modelXPosition) {}

void renderer::Render() {
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(glm::value_ptr(view));
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(projection));

    for (unsigned int i = 0; i < scene->mNumMeshes; ++i) {
        const aiMesh* mesh = scene->mMeshes[i];
        RenderModel(mesh);
    }
}

void renderer::RenderModel(const aiMesh* mesh) {
    glBegin(GL_TRIANGLES);
    for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
        const aiFace& face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; ++j) {
            unsigned int index = face.mIndices[j];
            glVertex3f(mesh->mVertices[index].x + modelXPosition, mesh->mVertices[index].y, mesh->mVertices[index].z);
        }
    }
    glEnd();
}