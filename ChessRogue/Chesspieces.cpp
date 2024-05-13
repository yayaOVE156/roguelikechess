#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Chesspieces.h"
#include "render.h"

BasePiece::BasePiece(float modelXPosition, float modelZPosition)
    :modelXPosition(modelXPosition), modelZPosition(modelZPosition) {}

void BasePiece::Render(const glm::mat4& view, const glm::mat4& projection) {
    Assimp::Importer importer;
    scene = importer.ReadFile(modelPath, aiProcess_Triangulate | aiProcess_FlipUVs);
    std::cout << scene << std::endl;
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

void BasePiece::RenderModel(const aiMesh* mesh) {
    glBegin(GL_TRIANGLES);
    for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
        const aiFace& face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; ++j) {
            unsigned int index = face.mIndices[j];
            glVertex3f(0.5f*mesh->mVertices[index].x + modelXPosition, 0.5f * mesh->mVertices[index].y, 0.5f * mesh->mVertices[index].z + modelZPosition);
        }
    }
    glEnd();
}

Pawn::Pawn( float modelXPosition, float modelZPosition)
    : BasePiece( modelXPosition, modelZPosition) {
    modelPath = "../OpenGL Models/pawn.obj";
    
}




Rook::Rook( float modelXPosition, float modelZPosition)
    : BasePiece( modelXPosition, modelZPosition) {
    modelPath = "../OpenGL Models/rook.obj";
    Assimp::Importer importer;
    scene = importer.ReadFile(modelPath, aiProcess_Triangulate | aiProcess_FlipUVs);
}

Knight::Knight( float modelXPosition, float modelZPosition)
    : BasePiece( modelXPosition, modelZPosition) {
    modelPath = "../OpenGL Models/knight.obj";
    Assimp::Importer importer;
    scene = importer.ReadFile(modelPath, aiProcess_Triangulate | aiProcess_FlipUVs);
}

Bishop::Bishop( float modelXPosition, float modelZPosition)
    : BasePiece( modelXPosition, modelZPosition) {
    modelPath = "../OpenGL Models/bishop.obj";
    Assimp::Importer importer;
    scene = importer.ReadFile(modelPath, aiProcess_Triangulate | aiProcess_FlipUVs);
}

Queen::Queen( float modelXPosition, float modelZPosition)
    : BasePiece( modelXPosition, modelZPosition) {
    modelPath = "../OpenGL Models/queen.obj";
    Assimp::Importer importer;
    scene = importer.ReadFile(modelPath, aiProcess_Triangulate | aiProcess_FlipUVs);
}

King::King( float modelXPosition, float modelZPosition)
    : BasePiece( modelXPosition, modelZPosition) {
    modelPath = "../OpenGL Models/king.obj";
    Assimp::Importer importer;
    scene = importer.ReadFile(modelPath, aiProcess_Triangulate | aiProcess_FlipUVs);
}
