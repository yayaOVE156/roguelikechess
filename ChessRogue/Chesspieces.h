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


//base piece class
// it is the base foundation for the rest of the pieces
// it has a model path, a scene, and a render model function


struct XZ {
    float x;
    float z;

    XZ() : x(0.0f), z(0.0f) {}

    XZ(float x, float z) : x(x), z(z) {}

    // Overloading the '<' operator for XZ
    bool operator<(const XZ& other) const {
        // Compare based on x value first, then z value
        if (x != other.x)
            return x < other.x;
        return z < other.z;
    }

    
};

     const extern aiScene* scene;

class BasePiece {
protected:
    std::string modelPath;
    


public:
    XZ position;
    bool black = false;
    BasePiece(float modelXPosition, float modelZPosition, bool black);
    void Load(const glm::mat4& view, const glm::mat4& projection);
    void RenderModel(const aiMesh* mesh);
    const static aiScene* getScene() {
        return scene;
    }
    int weight;
    

};

class Pawn : public BasePiece {
public:
    Pawn(float modelXPosition, float modelZPosition,bool black);

};

class Rook : public BasePiece {
public:
    Rook( float modelXPosition, float modelZPosition, bool black);
};

class Knight : public BasePiece {
public:
    Knight( float modelXPosition, float modelZPosition, bool black);
};

class Bishop : public BasePiece {
public:
    Bishop( float modelXPosition, float modelZPosition, bool black);
};

class Queen : public BasePiece {
public:
    Queen( float modelXPosition, float modelZPosition, bool black);
};

class King : public BasePiece {
public:
    King( float modelXPosition, float modelZPosition, bool black);
};

#endif // CHESSPIECES_H
