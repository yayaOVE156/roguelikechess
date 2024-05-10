#ifndef CHESSPIECES_H
#define CHESSPIECES_H

#include <string>
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>





class BasePiece {
protected:
    std::string modelPath;
    const aiScene* scene;
    

    void RenderModel(const aiMesh* mesh);

public:
    float modelXPosition;
    float modelZPosition;
    BasePiece(float modelXPosition, float modelZPosition);
    void Render(const glm::mat4& view, const glm::mat4& projection);
    
};

class Pawn : public BasePiece {
public:
    Pawn(float modelXPosition, float modelZPosition);

};

class Rook : public BasePiece {
public:
    Rook( float modelXPosition, float modelZPosition);
};

class Knight : public BasePiece {
public:
    Knight( float modelXPosition, float modelZPosition);
};

class Bishop : public BasePiece {
public:
    Bishop( float modelXPosition, float modelZPosition);
};

class Queen : public BasePiece {
public:
    Queen( float modelXPosition, float modelZPosition);
};

class King : public BasePiece {
public:
    King( float modelXPosition, float modelZPosition);
};

#endif // CHESSPIECES_H
