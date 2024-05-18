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
#include <vector>


//base piece class
// it is the base foundation for the rest of the pieces
// it has a model path, a scene, and a render model function

     const extern aiScene* scene;

class BasePiece {

private:
    std::vector<float> vertices;
    bool loaded = false;
    GLuint VBO, VAO;
    void SetupMesh(const aiMesh* mesh);

public:
    std::string modelPath;
    float modelXPosition;
    float modelZPosition;
    BasePiece(float modelXPosition, float modelZPosition);
    void LoadModel();
    void RenderModel(const glm::mat4& view, const glm::mat4& projection);
    bool checkLoaded() {
        return loaded;
    };
    std::string checkModelPath() {
        return modelPath;
    }
    
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
