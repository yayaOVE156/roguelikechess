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

BasePiece::BasePiece(float modelXPosition, float modelZPosition,bool black)
    :position(modelXPosition,modelZPosition), black(black) {}


// Render function for the base piece class

void BasePiece::Load(const glm::mat4& view, const glm::mat4& projection) {
    //maybe inefficient as it loads the model everytime the Render() function is called
    // a possible soltuion is to load the model in the constructor using a different pointer that points to the start address of the model
    // then everytime the Render() is called a different pointer points to the start address of the model pointer
    // think of it as like an for loop where int i is init outside of the loop, but when the loop starts it is set to 0
    Assimp::Importer importer;
    scene = importer.ReadFile(modelPath, aiProcess_Triangulate | aiProcess_FlipUVs);
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
//uses the mesh to render it on the window
void BasePiece::RenderModel(const aiMesh* mesh) {
    if(black)
		glColor3f(0.0f, 0.0f, 0.0f);
    else {
        glColor3f(1.0f, 1.0f, 1.0f);
    }
    glBegin(GL_TRIANGLES);
    for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
        const aiFace& face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; ++j) {
            unsigned int index = face.mIndices[j];
            glVertex3f(0.5f * mesh->mVertices[index].x + position.x, 0.5f * mesh->mVertices[index].y+1.0, 0.5f * mesh->mVertices[index].z + position.z);
        }
    }
    glEnd();
}

Pawn::Pawn( float modelXPosition, float modelZPosition, bool black)
    : BasePiece( modelXPosition, modelZPosition,  black) {
    modelPath = "../OpenGL Models/pawn.obj";
    weight = 1;
}

// rest of the pieces except they load the model first, but they are not used as the pawn is used for
// testing purposes


Rook::Rook( float modelXPosition, float modelZPosition, bool black)
    : BasePiece( modelXPosition, modelZPosition,  black) {
    modelPath = "../OpenGL Models/rook.obj";
   weight = 3;
}

Knight::Knight( float modelXPosition, float modelZPosition, bool black)
    : BasePiece( modelXPosition, modelZPosition,  black) {
    modelPath = "../OpenGL Models/knight.obj";
    weight = 5;
}

Bishop::Bishop( float modelXPosition, float modelZPosition, bool black)
    : BasePiece( modelXPosition, modelZPosition,  black) {
    modelPath = "../OpenGL Models/bishop.obj";
    weight = 3;
}

Queen::Queen( float modelXPosition, float modelZPosition, bool black)
    : BasePiece( modelXPosition, modelZPosition,  black) {
    modelPath = "../OpenGL Models/queen.obj";
    weight = 9;
}

King::King( float modelXPosition, float modelZPosition, bool black)
    : BasePiece( modelXPosition, modelZPosition,  black) {
    modelPath = "../OpenGL Models/king.obj";
     weight = 100;
}
