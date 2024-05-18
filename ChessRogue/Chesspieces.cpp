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

const aiScene* scene;

BasePiece::BasePiece(float modelXPosition, float modelZPosition)
    :modelXPosition(modelXPosition), modelZPosition(modelZPosition), loaded(false) {
    LoadModel();
}


// Render function for the base piece class

void BasePiece::LoadModel() {
    //maybe inefficient as it loads the model everytime the Render() function is called
    // a possible soltuion is to load the model in the constructor using a different pointer that points to the start address of the model
    // then everytime the Render() is called a different pointer points to the start address of the model pointer
    // think of it as like an for loop where int i is init outside of the loop, but when the loop starts it is set to 0
    Assimp::Importer importer;
    scene = importer.ReadFile(modelPath, aiProcess_Triangulate | aiProcess_FlipUVs);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "Error loading model: " << importer.GetErrorString() << std::endl;
        return;
    }
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    for (unsigned int i = 0; i < scene->mNumMeshes; ++i) {
        const aiMesh* mesh = scene->mMeshes[i];
        SetupMesh(mesh);
    }

    loaded = true;
   /* glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(glm::value_ptr(view));
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(projection));*/
    
}

void BasePiece::SetupMesh(const aiMesh* mesh) {
    for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
        vertices.push_back(mesh->mVertices[i].x);
        vertices.push_back(mesh->mVertices[i].y);
        vertices.push_back(mesh->mVertices[i].z);
    }

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

//uses the mesh to render it on the window
void BasePiece::RenderModel(const glm::mat4& view, const glm::mat4& projection) {
    /*glBegin(GL_TRIANGLES);
    for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
        const aiFace& face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; ++j) {
            unsigned int index = face.mIndices[j];
            glVertex3f(0.5f*mesh->mVertices[index].x + modelXPosition, 0.5f * mesh->mVertices[index].y, 0.5f * mesh->mVertices[index].z + modelZPosition);
        }
    }
    glEnd();*/

    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(glm::value_ptr(view));

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 3);
    glBindVertexArray(0);

}

Pawn::Pawn( float modelXPosition, float modelZPosition)
    : BasePiece( modelXPosition, modelZPosition) {
    modelPath = "../OpenGL Models/Pawn.obj";
    
}

// rest of the pieces except they load the model first, but they are not used as the pawn is used for
// testing purposes


Rook::Rook( float modelXPosition, float modelZPosition)
    : BasePiece( modelXPosition, modelZPosition) {
    modelPath = "../OpenGL Models/Rook.obj";
    Assimp::Importer importer;
    scene = importer.ReadFile(modelPath, aiProcess_Triangulate | aiProcess_FlipUVs);
}

Knight::Knight( float modelXPosition, float modelZPosition)
    : BasePiece( modelXPosition, modelZPosition) {
    modelPath = "../OpenGL Models/Knight.obj";
    Assimp::Importer importer;
    scene = importer.ReadFile(modelPath, aiProcess_Triangulate | aiProcess_FlipUVs);
}

Bishop::Bishop( float modelXPosition, float modelZPosition)
    : BasePiece( modelXPosition, modelZPosition) {
    modelPath = "../OpenGL Models/Bishop.obj";
    Assimp::Importer importer;
    scene = importer.ReadFile(modelPath, aiProcess_Triangulate | aiProcess_FlipUVs);
}

Queen::Queen( float modelXPosition, float modelZPosition)
    : BasePiece( modelXPosition, modelZPosition) {
    modelPath = "../OpenGL Models/Queen.obj";
    Assimp::Importer importer;
    scene = importer.ReadFile(modelPath, aiProcess_Triangulate | aiProcess_FlipUVs);
}

King::King( float modelXPosition, float modelZPosition)
    : BasePiece( modelXPosition, modelZPosition) {
    modelPath = "../OpenGL Models/King.obj";
    Assimp::Importer importer;
    scene = importer.ReadFile(modelPath, aiProcess_Triangulate | aiProcess_FlipUVs);
}
