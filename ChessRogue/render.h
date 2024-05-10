#include <GL/glew.h>
#include <GL/glut.h>
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




class renderer {
public:
    renderer(const aiScene* scene, const glm::mat4& view, const glm::mat4& projection, float modelXPosition);
    void Render();

private:
    const aiScene* scene;
    glm::mat4 view;
    glm::mat4 projection;
    float modelXPosition;

    void RenderModel(const aiMesh* mesh);
};